# ROS 2 Humble Installation via WSL2 on Windows

## Overview
This guide documents the full process of installing **ROS 2 Humble Hawksbill** on a Windows laptop using **WSL2** with **Ubuntu 22.04**. It includes every command used, the errors encountered along the way, and how each was resolved.

## Prerequisites
- Windows 10/11 with virtualization enabled in BIOS
- Administrator access to PowerShell
- Stable internet connection
- At least 10 GB free disk space (ROS 2 Desktop + Ubuntu image)

## System Info
| Component | Version |
|---|---|
| Host OS | Windows 10/11 |
| WSL Version | 2 |
| Linux Distro | Ubuntu 22.04 (Jammy) |
| ROS 2 Distro | Humble Hawksbill |

## Installation Steps

### 1. Check existing WSL distros
```bash
wsl -l -v
```

### 2. Install Ubuntu 22.04
Humble only supports Ubuntu 22.04 (jammy), not 24.04 (noble):
```bash
wsl --install -d Ubuntu-22.04
```
Set a Unix username and password when prompted.

### 3. Update the system
```bash
cd
sudo apt update && sudo apt upgrade -y
```

### 4. Install prerequisites and enable universe repo
```bash
sudo apt install software-properties-common curl -y
sudo add-apt-repository universe
```

### 5. Add the ROS 2 GPG key
```bash
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
```

### 6. Add the Humble repository
```bash
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu jammy main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null
sudo apt update
```

### 7. Install ROS 2 Humble Desktop + dev tools
```bash
sudo apt install ros-humble-desktop
sudo apt install ros-dev-tools
```

### 8. Source ROS permanently
```bash
echo "source /opt/ros/humble/setup.bash" >> ~/.bashrc
source ~/.bashrc
```

### 9. Verify installation
```bash
echo $ROS_DISTRO
ros2 pkg list

```
<img width="300" height="40" alt="لقطة شاشة 2026-08-01 183850" src="https://github.com/user-attachments/assets/1471237c-6932-4c2e-8d6b-7a411fc91c51" />


## Errors Encountered and Fixes

| # | Error | Cause | Fix |
|---|---|---|---|
| 1 | "This app can't run on your PC" when opening Ubuntu from Microsoft Store | Store search returned website shortcuts, not the real app | Installed via `wsl --install -d Ubuntu-22.04` in PowerShell instead of the Store |
| 2 | `cd~: command not found` / `cd [char]126` | Keyboard layout conflict broke the tilde (`~`) character | Used `cd` alone, or `cd /home/<username>` |
| 3 | Tried installing Humble on Ubuntu 24.04 (noble) | ROS 2 Humble has no official binaries for noble | Installed a dedicated Ubuntu 22.04 WSL instance |
| 4 | `ros2: command not found` | ROS environment not sourced in the terminal | Ran `source /opt/ros/humble/setup.bash` manually, fixed `.bashrc` |
| 5 | `bash: source: /opt/ros/humble: is a directory` | Stray space in path (`/opt/ros/humble /setup.bash`) | Corrected to `/opt/ros/humble/setup.bash` (no space) |
| 6 | `.bashrcsource` file created accidentally | Missing space in `echo` command merged `~/.bashrc` and `source` | Removed bad file (`rm -f ~/.bashrcsource`), re-ran `echo` correctly |
| 7 | `ros2: error: unrecognized arguments: --version` | `ros2` CLI has no `--version` flag | Used `echo $ROS_DISTRO` and `ros2 pkg list` instead |

## Verification Test
Confirmed with a two-terminal talker/listener test:
```bash
# Terminal 1
ros2 run demo_nodes_cpp talker

# Terminal 2
ros2 run demo_nodes_cpp listener
```
Successful message exchange between terminals confirms a working ROS 2 Humble installation.

## Result
✅ ROS 2 Humble installed and running successfully on Ubuntu 22.04 via WSL2.

## References
- [ROS 2 Humble Official Installation Docs](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html)
- [Microsoft WSL Documentation](https://learn.microsoft.com/en-us/windows/wsl/install)

## Author / Team
- Name:
- Course / Project:
- Date: August 2026
