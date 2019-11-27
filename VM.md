# Setting up your VM
Instructions for setting up your crash-test dummy VirtualBox VM:

## Pre-setup

### Networking
Prepare a host-only network: you will need this for SSH access to the machine
You may need to add yourself to the `vboxusers` group in order to be able to create this network.
On Debian based systems you could use:

```sh
adduser <you> vboxusers
```

### Debian Installation ISO
Use Debian netinstall as it will not require 'much' hard disk space, but still be familiar to most people. Easiest thing is to grab [the latest AMD64 Netinstall image](https://cdimage.debian.org/cdimage/daily-builds/daily/arch-latest/amd64/iso-cd/)

## Provisioning
Mostly defaults:

 - 1GB RAM
 - 8GB disk (you can go smaller but YMMV).
 - 1 CPU core, capped at 100% CPU

Cnfigure two network adapters:

  1. NAT
  2. Host-only: the network you prepared earlier

Make sure to mount the downloaded installer image (ISO) as a CD drive (IDE).
Nota Bene: it is recommended to leave EFI support disabled, it is only serves to make things more complicated.

After specifying the specs of your VM, you will need to 'fix' DNS for the VM by running:

```sh
VBoxManage modifyvm "<VM name>" --natdnshostresolver1 on
```

## Install:
For the most parts the defaults will work fine, or things are easy enough to configure to your liking (e.g. language). Some exceptions apply:

### Components
Make sure to load `mbr` and partitioning related udebs (modules).

### Paritioning
Do not use defaults: instead manually partition your disk. Use a single `/` partition covering the entire disk. In particular make sure to avoid configuring any swap.

### Installing software
Do not install a desktop environment. A SSH server, on the other hand, would be useful.

## First run
Install packages. Some useful ones:

```sh
apt-get install --no-install-recommends docker.io docker-compose aptitude ssh tmux psmisc git gcc perl libc6-dev
```

Note: to simplify working with `docker` you may want to add your user account to the `docker` group, using:

```sh
/usr/sbin/adduser <you> docker
```

Fix networking: only one adapter will be configured by default, and you will want to be able to use both. Use:
```sh
ip addr
```

Note the Ethernet card which has no IP (e.g. `enp0s8`), and then edit `/etc/network/interfaces` to add:
```
allow-hotplug <name>
iface <name> inet dhcp
```

## Reboot
At this point you should be able to:

 - Have both Ethernet interfaces come up with an address obtained via DHCP (check `ip addr` output)
 - Be able to SSH into the machine via the second interface (`ssh <you>@<ip>`)
 - Be able to execute docker commands (`docker version`) without requiring root
 - Have plenty of disk space left over (`df -H /`), should indicate <20% usage out of 8GB
 - Be able to start with the exercises!
