odin (Xiaomi MIX 4) KernelSU 5.4 LKM 构建产物
================================================
android11-5.4_kernelsu.ko   ELF64 aarch64 内核模块，供 ksud late-load 使用
device.config               从官方 OTA OS1.0.8.0.UKMCNXM 的 boot.img 提取的真实内核配置
undefined-symbols.txt       模块的 194 个未定义符号（ksuinit 运行时用 /proc/kallsyms 绑定）

设备内核: 5.4.259-qgki-g8cc268997371
源码树  : MiCode/Xiaomi_Kernel_OpenSource @ odin-r-oss (5.4.86)

用法:
  adb push ksud-aarch64-linux-android /data/local/tmp/ksud
  adb push android11-5.4_kernelsu.ko   /data/local/tmp/
  adb shell chmod +x /data/local/tmp/ksud
  # 在有 root 的 shell 里:
  /data/local/tmp/ksud insmod /data/local/tmp/android11-5.4_kernelsu.ko
