# Dokumentasi Setup Simulasi ORCA AUV di Gazebo

Repositori ini berisi panduan langkah demi langkah untuk melakukan *setup* dan menjalankan lingkungan simulasi Autonomous Underwater Vehicle (AUV) **ORCA** menggunakan **ROS 2**, **Gazebo Harmonic**, dan **ArduPilot (ArduSub)**.

---

## 📌 Prasyarat Sistem & Kompatibilitas OS

Pilih versi ROS 2 yang sesuai dengan distro Ubuntu yang Anda gunakan:

- **Ubuntu 22.04 LTS (Jammy Jellyfish)** $\rightarrow$ Disarankan menggunakan **ROS 2 Humble Hawksbill**  
  *(Dokumentasi resmi: [ROS 2 Humble Installation](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html))*
- **Ubuntu 24.04 LTS (Noble Numbat)** $\rightarrow$ Disarankan menggunakan **ROS 2 Jazzy Jalisco**  
  *(Dokumentasi resmi: [ROS 2 Jazzy Installation](https://docs.ros.org/en/jazzy/Installation/Ubuntu-Install-Debs.html))*

---

## 🛠️ 1. Setup Environment ROS 2

Langkah ini bertujuan untuk memastikan versi Ubuntu Anda mendukung versi ROS 2 yang dipilih serta mengonfigurasi variabel lingkungan (*environment variables*) agar perintah `ros2` dapat dipanggil secara otomatis di setiap sesi terminal.

### Perintah Terminal:
```bash
# 1. Cek versi Ubuntu yang sedang digunakan
lsb_release -a

# 2. Cek apakah ROS 2 sudah terinstall dan variabel ROS_DISTRO sudah aktif
echo $ROS_DISTRO

# 3. Buka file konfigurasi shell .bashrc
nano ~/.bashrc
```

**Penjelasan Modifikasi File `~/.bashrc`:**  
Tambahkan salah satu baris berikut di paling bawah file `~/.bashrc` sesuai dengan distro ROS 2 yang Anda gunakan:

```bash
# Untuk ROS 2 Humble (Ubuntu 22.04)
source /opt/ros/humble/setup.bash

# Untuk ROS 2 Jazzy (Ubuntu 24.04)
source /opt/ros/jazzy/setup.bash
```
*Gunakan tombol `CTRL+X`, tekan `Y`, lalu `Enter` untuk menyimpan.*

```bash
# 4. Muat ulang konfigurasi .bashrc agar perubahan langsung aktif
source ~/.bashrc
```

---

## 🌐 2. Setup Gazebo Harmonic

Gazebo Harmonic adalah simulator 3D yang digunakan untuk merepresentasikan lingkungan fisik laut dan dinamika robot AUV ORCA.  
*(Dokumentasi resmi: [Gazebo Harmonic Installation](https://gazebosim.org/docs/harmonic/install_ubuntu/))*

### Perintah Terminal:
```bash
# Cek versi Gazebo Harmonic yang terpasang pada sistem
gz sim --versions

# Menjalankan aplikasi simulator Gazebo secara manual untuk verifikasi
gz sim
```

---

## 📦 3. Instalasi Paket Pendukung Model 3D Robot di ROS 2

Paket-paket ini diperlukan oleh ROS 2 untuk memproses deskripsi kinematika robot (`URDF` & `Xacro`) serta menyediakan *bridge* komunikasi antara ROS 2 dan Gazebo Harmonic (`ros_gz`).

### Untuk ROS 2 Humble:
```bash
sudo apt update
sudo apt install -y ros-humble-urdf-tutorial ros-humble-xacro ros-humble-ros-gz
```

### Untuk ROS 2 Jazzy:
```bash
sudo apt update
sudo apt install -y ros-jazzy-urdf-tutorial ros-jazzy-xacro ros-jazzy-ros-gz
```

**Penjelasan Paket:**
- `xacro` / `urdf`: Memungkinkan parsing struktur 3D dan visualisasi robot.
- `ros-gz`: Mengintegrasikan *topic* dan *service* antara ROS 2 dan simulator Gazebo.

---

## 📂 4. Clone Repositori Workspace ORCA

Mengunduh repositori kerja utama (*workspace*) yang berisi deskripsi model robot AUV ORCA dan paket pengontrolnya.

```bash
# Pindah ke direktori home
cd ~

# Mengklon repositori workspace ORCA
git clone https://github.com/ChristianRiovaldo/orca_ws.git
```

---

## ✈️ 5. Setup ArduPilot & Plugin ArduPilot Gazebo

ArduPilot bertindak sebagai pengontrol penerbangan/pelayaran (*Autopilot*) bawaan untuk AUV (ArduSub). Plugin `ardupilot_gazebo` dibutuhkan agar Pixhawk virtual dapat mengendalikan model robot di dalam simulasi Gazebo.

```bash
# 1. Pindah ke direktori home
cd ~

# 2. Clone repositori ArduPilot beserta seluruh sub-modulnya
git clone https://github.com/ArduPilot/ardupilot.git --recursive

# 3. Clone plugin jembatan komunikasi antara ArduPilot dan Gazebo
git clone https://github.com/ArduPilot/ardupilot_gazebo

# 4. Install paket dependensi pemroses media (GStreamer) untuk kebutuhan streaming kamera simulasi
sudo apt update
sudo apt install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav

# 5. Build plugin ArduPilot Gazebo untuk menghasilkan file binary (libArduPilotPlugin.so)
cd ~/ardupilot_gazebo
mkdir build && cd build
cmake ..
make -j$(nproc)
```

---

## 🔧 6. Konfigurasi Environment Simulasi

Agar Gazebo dapat menemukan model 3D AUV ORCA dan plugin ArduPilot, kita harus mendaftarkan direktori *resource* dan *plugin* ke dalam variabel lingkungan sistem.

```bash
nano ~/.bashrc
```

**Tambahkan baris berikut di bagian paling bawah file `~/.bashrc`:**
```bash
# Menghapus cache variabel lama agar tidak konflik
unset GZ_SIM_RESOURCE_PATH
unset GZ_SIM_SYSTEM_PLUGIN_PATH

# Mengarahkan path direktori aset 3D AUV dan plugin ArduPilot
export GZ_SIM_RESOURCE_PATH=$GZ_SIM_RESOURCE_PATH:~/orca_ws/install/auv_description/share
export GZ_SIM_SYSTEM_PLUGIN_PATH=~/ardupilot_gazebo/build
```
*Catatan: Sesuaikan struktur folder `orca_ws` apabila lokasi repositori Anda berbeda.*

```bash
# Muat ulang konfigurasi .bashrc
source ~/.bashrc
```

---

## 📡 7. Instalasi MAVProxy

MAVProxy adalah Ground Control Station (GCS) berbasis CLI (*Command Line Interface*) berbasis Python yang digunakan untuk mentransmisikan protokol MAVLink dari ArduPilot ke ROS / GCS lainnya.

Untuk dokumentasi lengkap dan cara instalasinya, silakan merujuk ke:  
👉 [Dokumentasi Instalasi MAVProxy Official](https://ardupilot.org/mavproxy/docs/getting_started/download_and_installation.html)

---

## 🚀 8. Menjalankan Simulasi ORCA di Gazebo

Untuk menjalankan simulasi secara lengkap, Anda memerlukan **4 jendela terminal** yang dibuka secara berurutan.

### 📍 Terminal 1: Build Workspace & Launch World Gazebo
Perintah ini mengompilasi paket ROS 2 lalu memuat model 3D AUV ke dalam simulator Gazebo.
```bash
cd ~/orca_ws
colcon build
source install/setup.bash
ros2 launch auv_bringup auv_gazebo.launch.py
```
> ⚠️ **Penting:** Setelah lingkungan 3D terbuka di Gazebo, klik tombol **"Play/Run simulation"** (tombol oranye/hijau di pojok kiri bawah layar Gazebo) sebelum melanjut ke Terminal 2.

---

### 📍 Terminal 2: Jalankan SITL ArduPilot (Virtual Pixhawk)
Menjalankan software-in-the-loop (SITL) ArduSub dengan profil AUV 6-DOF (*Degree of Freedom*) dan koneksi UDP.
```bash
cd ~/ardupilot
Tools/autotest/sim_vehicle.py -L RATBeach -v ArduSub -f vectored_6dof --model=JSON --out=udp:0.0.0.0:14550 --out=udp:0.0.0.0:14551 --console
```

---

### 📍 Terminal 3: Jalankan Bridge Pengontrol (`control_bridge`)
Menjalankan *node* ROS 2 yang menjembatani perintah kontrol MAVLink/ROS 2 ke sistem penggerak AUV.
```bash
cd ~/orca_ws
source install/setup.bash
ros2 run mavpy control_bridge
```

---

### 📍 Terminal 4: Teleop Keyboard
Menjalankan node kontrol keyboard untuk memandu gerakan AUV ORCA secara manual.
```bash
cd ~/orca_ws
source install/setup.bash
ros2 run mavpy keyboard
```

---

## 🎛️ (Opsional) Ground Control Station - QGroundControl

Untuk memantau telemetri AUV, orientasi sensor, attitude, serta merencanakan misi autonomous secara visual, Anda dapat menginstall software **QGroundControl (QGC)**.

- **Unduh & Dokumentasi QGC:** [QGroundControl User Guide](https://docs.qgroundcontrol.com/master/en/qgc-user-guide/getting_started/download_and_install.html)
- QGC akan otomatis terhubung ke AUV melalui port UDP `14550` yang dipancarkan oleh ArduPilot SITL pada **Terminal 2**.