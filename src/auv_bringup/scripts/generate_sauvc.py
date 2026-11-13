#!/usr/bin/env python3
"""Generate a randomized SAUVC arena into an explicit writable output path."""
from pathlib import Path
import xml.etree.ElementTree as E
import math, json, argparse, random, secrets
parser=argparse.ArgumentParser()
parser.add_argument('--config',type=Path,required=True)
parser.add_argument('--template',type=Path,required=True)
parser.add_argument('--output',type=Path,required=True)
parser.add_argument('--seed',type=int)
args=parser.parse_args()
cfg=json.loads(args.config.read_text())
seed=args.seed if args.seed is not None else secrets.randbits(31)
rng=random.Random(seed)
cfg['layout_seed']=seed
blue=rng.randrange(4)
cfg['drum_colors']=['blue' if i==blue else 'red' for i in range(4)]
cfg['pinger_drum_index']=rng.choice([i for i in range(4) if i!=blue])
points=[]
for color in ['yellow','red','blue']:
 for attempt in range(10000):
  point=[rng.uniform(cfg['flare_bounds_x'][0]+.05,cfg['flare_bounds_x'][1]-.05),rng.uniform(cfg['flare_bounds_y'][0]+.05,cfg['flare_bounds_y'][1]-.05)]
  if all(math.dist(point,q)>=cfg['flare_min_separation'] for q in points):break
 else:raise ValueError('Cannot fit separated flares inside configured box')
 points.append(point);cfg['flares'][color]=point
args.output.parent.mkdir(parents=True,exist_ok=True)
args.output.with_suffix('.layout.json').write_text(json.dumps(cfg,indent=2)+'\n')
print(f'ORCA SAUVC V6 seed={seed}; blue bucket slot={blue+1}; flares={points}')
def sub(parent,tag,text=None,**attrs):
 e=E.SubElement(parent,tag,attrs)
 if text is not None:e.text=str(text)
 return e
base=E.parse(args.template)
w=base.getroot().find('world')
for model in list(w.findall('model')):w.remove(model)
w.find('scene/ambient').text='0.65 0.65 0.65 1'
w.find('scene/background').text='0.65 0.82 0.94 1'
scene=w.find('scene')
for el in list(scene.findall('fog')):scene.remove(el)
grid=scene.find('grid')
if grid is None:grid=E.SubElement(scene,'grid')
grid.text='false'
if cfg['water_fog_enabled']:
 fog=E.SubElement(scene,'fog')
 for tag,value in [('type','linear'),('color','0.12 0.48 0.65 1'),('start',cfg['water_fog_start']),('end',cfg['water_fog_end']),('density',.01)]:
  E.SubElement(fog,tag).text=str(value)
colors={'tile':'0.65 0.86 0.94 1','white':'0.94 0.96 0.96 1','black':'0.035 0.045 0.055 1','orange':'1 0.36 0.01 1','red':'0.85 0.015 0.025 1','green':'0.02 0.85 0.1 1','blue':'0.01 0.25 0.8 1','yellow':'1 0.85 0.01 1'}
def model(name):
 m=sub(w,'model',name=name);sub(m,'static','true');return sub(m,'link',name='link')
def shape(link,name,xyz,size,color='tile',rpy=(0,0,0),collision=True,kind='box'):
 for tag in (['collision','visual'] if collision else ['visual']):
  el=sub(link,tag,name=name);sub(el,'pose',' '.join(map(str,[*xyz,*rpy])))
  g=sub(sub(el,'geometry'),kind)
  if kind=='box':sub(g,'size',' '.join(map(str,size)))
  elif kind=='sphere':sub(g,'radius',size[0])
  else:sub(g,'radius',size[0]);sub(g,'length',size[1])
  if tag=='visual':
   mat=sub(el,'material');sub(mat,'ambient',colors[color]);sub(mat,'diffuse',colors[color])
def floor_z(x):
 if x<=cfg['shallow_flat_end']:return -cfg['shallow_depth']
 if x>=cfg['slope_end']:return -cfg['deep_depth']
 return -cfg['shallow_depth']-(cfg['deep_depth']-cfg['shallow_depth'])*(x-cfg['shallow_flat_end'])/(cfg['slope_end']-cfg['shallow_flat_end'])
def slab(link,name,a,b,color='tile',y=0,width=25,t=.15,offset=0):
 za,zb=floor_z(a)+offset,floor_z(b)+offset
 angle=math.atan2(za-zb,b-a)
 # Top face endpoints match intended floor, including thickness-normal offset.
 shape(link,name,((a+b)/2-math.sin(angle)*t/2,y,(za+zb)/2-math.cos(angle)*t/2),(math.hypot(b-a,zb-za),width,t),color,(0,angle,0),collision=not name.startswith(('grout','lane_blue')))
segments=[(0,cfg['shallow_flat_end']),(cfg['shallow_flat_end'],cfg['slope_end']),(cfg['slope_end'],cfg['length'])]
pool=model('sauvc_pool')
for a,b in segments:slab(pool,f'floor_{a}',a,b)
for y in [-12.65,12.65]:shape(pool,f'side_{y}',(25,y,-.9),(50.6,.3,2.6),'white')
for x in [-.15,50.15]:shape(pool,f'end_{x}',(x,0,-.9),(.3,25,2.6),'white')
# Rim and surrounding deck, collision only outside the water footprint.
for y in [-13.4,13.4]:shape(pool,f'deck_side_{y}',(25,y,.1),(52.4,1.8,.2),'white')
for x in [-.9,50.9]:shape(pool,f'deck_end_{x}',(x,0,.1),(1.8,25,.2),'white')
# Geometric tile pattern avoids external texture dependencies.
for y in range(-12,13):
 for a,b in segments:slab(pool,f'grout_y_{y}_{a}',a,b,'white',y,.018,.003,.004)
for x in range(1,50):shape(pool,f'grout_x_{x}',(x,0,floor_z(x)+.004),(.018,25,.004),'white',collision=False)
# Dark blue bottom lanes: pure visual markings following every floor segment.
lanes=model('blue_floor_lanes_with_T_ends')
for i,yy in enumerate(cfg['blue_lane_centers']):
 for j,(a,b) in enumerate(segments):
  a=max(a,cfg['blue_lane_start']);b=min(b,cfg['blue_lane_end'])
  if b>a:slab(lanes,f'lane_blue_{i}_{j}',a,b,'blue',yy,cfg['blue_lane_width'],.003,.012)
 for side,xx in [('start',cfg['blue_lane_start']),('end',cfg['blue_lane_end'])]:
  shape(lanes,f'T_{i}_{side}',(xx,yy,floor_z(xx)+.0105),(cfg['blue_lane_width'],cfg['blue_lane_t_width'],.003),'blue',collision=False)
# User removed qualification boundary markings; preserve tile pattern and blue lanes.
def square(name,center,size,markers=False):
 l=model(name);x,y=center;t=cfg['frame_tube_diameter']
 # Frame centerlines enclose nominal clear opening (pipe thickness is a modeling assumption).
 d=size/2+t/2
 for i,sign in enumerate([-1,1]):
  shape(l,f'x_{i}',(x+sign*d,y,0),(t/2,size+2*t),'white',rpy=(math.pi/2,0,0),kind='cylinder')
  shape(l,f'y_{i}',(x,y+sign*d,0),(t/2,size+2*t),'white',rpy=(0,math.pi/2,0),kind='cylinder')
  if markers:
   drop=cfg['surfacing_marker_drop']
   shape(l,f'marker_x_{i}',(x+sign*d,y,-drop/2),(t,.12,drop),'blue')
   shape(l,f'marker_y_{i}',(x,y+sign*d,-drop/2),(.12,t,drop),'blue')
square('starting_zone',cfg['starting_center'],cfg['starting_size'])
square('surfacing_square',cfg['surfacing_center'],cfg['surfacing_size'],True)
def gate(name,x,y,width,height,main=False):
 l=model(name);t=cfg['post_thickness']
 # Explicit training adaptation: legs reach the floor, while top stays at surface.
 if not main and cfg['qualification_mount']=='floor_supported_training':
  z=floor_z(x);height=-z
 else:z=floor_z(x) if main else -height
 # 1.5 m interpreted as clear opening; 4 cm posts lie outside it.
 for i,sign in enumerate([-1,1]):
  px,py=(x+sign*(width+t)/2,y) if main else (x,y+sign*(width+t)/2)
  shape(l,f'post_{i}',(px,py,z+height/2),(t,t,height),'black' if main else 'orange')
  if main:
   # Approximate 20 cm color / 10 cm black stripe pattern from Figure 11.
   for j in range(5):
    low=.04+j*.30;h=min(.20,height-low)
    if h>0:shape(l,f'stripe_{i}_{j}',(px,py,z+low+h/2),(t+.001,t+.001,h),'red' if i==0 else 'green',collision=False)
 shape(l,'crossbar',(x,y,z+height+t/2),(width+2*t,t,t) if main else (t,width+2*t,t),'black' if main else 'white')
for i,y in enumerate(cfg['qualification_lanes_y'],1):
 gate(f'qualification_gate_{i}',cfg['qualification_x'],y,cfg['qualification_gate_width'],cfg['qualification_gate_height'])
 l=model(f'qualification_start_{i}')
 shape(l,'wall_marker',(.005,y,0),(.01,1.,.08),'yellow',collision=False)
gate('gate',*cfg['main_gate_center'],cfg['main_gate_width'],cfg['main_gate_height'],True)
target=model('target_zone');x,y=cfg['target_center'];sx,sy=cfg['target_size']
z=floor_z(x)+.008
shape(target,'mat',(x,y,z),(sx,sy,.012),'green',collision=False)
# Native SDF primitives: explicit per-part color, no mesh/OBJ material dependency.
for i,dx in enumerate(cfg['drum_offsets']):
 l=model(f'open_bucket_v6_{i+1}');xx=x+dx;col=cfg['drum_colors'][i]
 h=cfg['drum_height'];r=cfg['drum_radius'];t=cfg['drum_wall_thickness']
 bottom=floor_z(xx)+.025;rb=r-.045;lip=.007;rt=r-lip
 shape(l,'bottom',(xx,y,bottom-t/2),(rb,t),col,kind='cylinder')
 # Floor is colored, never a lid; its upper face is 30 cm below lip top.
 n=24;top_center=rt-t/2;bot_center=rb-t/2;mid=(top_center+bot_center)/2
 tilt=math.atan2(top_center-bot_center,h)
 for k in range(n):
  a=2*math.pi*k/n
  shape(l,f'wall_{k}',(xx+mid*math.cos(a),y+mid*math.sin(a),bottom+h/2),(t,2*r*math.tan(math.pi/n),math.hypot(h,top_center-bot_center)),col,rpy=(0,tilt,a))
  # Rounded lip, short tangent cylinders following the circle, open at center.
  radius=r-lip;seg=2*radius*math.tan(math.pi/n)
  shape(l,f'rim_{k}',(xx+radius*math.cos(a),y+radius*math.sin(a),bottom+h-lip),(lip,seg),col,rpy=(0,math.pi/2,a+math.pi/2),kind='cylinder',collision=False)
 if i==cfg['pinger_drum_index']:
  shape(l,'pinger_placeholder',(xx+.10,y,bottom+.025),(.018,.05),'black',kind='cylinder')
for color,(x,y) in cfg['flares'].items():
 orange=color=='orange'
 h=cfg['orange_flare_height'] if orange else cfg['flare_height']
 r=cfg['orange_flare_radius'] if orange else cfg['flare_radius']
 z=floor_z(x)
 if orange:
  l=model('flare_orange')
  shape(l,'body',(x,y,z+h/2),(r,h),color,kind='cylinder')
  continue
 # Pole is a real dynamic rigid body, constrained by a ball joint at the floor.
 m=sub(w,'model',name='flare_'+color);sub(m,'static','false')
 sub(m,'pose',f'{x} {y} {z+.012} 0 0 0');sub(m,'self_collide','false')
 l=sub(m,'link',name='link');sub(l,'pose',f'0 0 {h/2} 0 0 0')
 inertial=sub(l,'inertial');mass=cfg['flare_mass'];sub(inertial,'mass',mass)
 inertia=sub(inertial,'inertia')
 for tag,value in [('ixx',mass*(3*r*r+h*h)/12),('iyy',mass*(3*r*r+h*h)/12),('izz',mass*r*r/2),('ixy',0),('ixz',0),('iyz',0)]:sub(inertia,tag,value)
 shape(l,'body',(0,0,0),(r,h),color,kind='cylinder')
 # Golf ball is attached in V6 so it returns with its pole, not a separate dropped ball.
 br=cfg['golf_ball_radius']
 shape(l,'golf_ball_tip',(0,0,h/2+br),(br,),'white',kind='sphere')
 joint=sub(m,'joint',name='floor_pivot',type='ball')
 sub(joint,'parent','world');sub(joint,'child','link')
 sub(joint,'pose','0 0 0 0 0 0',relative_to='__model__')
 for sensor_name,collision_name in [('bump_sensor','body'),('tip_bump_sensor','golf_ball_tip')]:
  sensor=sub(l,'sensor',name=sensor_name,type='contact')
  sub(sensor,'always_on','true');sub(sensor,'update_rate','0')
  contact=sub(sensor,'contact');sub(contact,'collision',collision_name)
 plugin=sub(m,'plugin',filename='libSauvcFlareRecovery.so',name='sauvc::FlareRecovery')
 sub(plugin,'robot_name','ORCA_V3');sub(plugin,'reset_seconds',cfg['flare_reset_seconds']);sub(plugin,'tip_torque',cfg['flare_tip_torque'])
# Visible water reference: purely visual, not a collision ceiling or fluid solver.
water=model('water_surface_z0_reference')
v=sub(water,'visual',name='surface');sub(v,'pose','25 0 0 0 0 0')
plane=sub(sub(v,'geometry'),'plane');sub(plane,'normal','0 0 1');sub(plane,'size','50 25')
mat=sub(v,'material');sub(mat,'ambient','0.15 0.6 0.8 1');sub(mat,'diffuse','0.15 0.6 0.8 1')
sub(v,'transparency',cfg['water_surface_transparency']);sub(v,'cast_shadows','false')
line=model('waterline_on_walls_z0')
for yy in [-12.49,12.49]:shape(line,f'y_{yy}',(25,yy,0),(50,.008,.035),'blue',collision=False)
for xx in [.01,49.99]:shape(line,f'x_{xx}',(xx,0,0),(.008,25,.035),'blue',collision=False)
# Floating reference collars explain qualification gate suspension.
for i,yy in enumerate(cfg['qualification_lanes_y'],1):
 lk=model(f'qualification_surface_floats_{i}')
 for side in [-1,1]:shape(lk,f'float_{side}',(cfg['qualification_x'],yy+side*.77,0),(.09,.09,.07),'white')
model('ORCA_SAUVC_V6_RANDOM_BOX_DYNAMIC_FLARES_BLUE_WATER')
# Surface frames are fixed at z=0; balls lack hydrodynamic drag/buoyancy.
E.indent(base,space='  ');base.write(args.output,encoding='unicode',xml_declaration=True)
