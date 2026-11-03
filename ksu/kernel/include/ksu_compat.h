#ifndef __KSU_COMPAT_H
#define __KSU_COMPAT_H

/*
 * KernelSU 5.4 兼容层（odin / msm-5.4 非 GKI）
 * 由 Kbuild 的 -include 强制注入到每个编译单元。
 */
#include <linux/version.h>
#include <linux/types.h>
#include <linux/sched/task.h>
#include <linux/sched/signal.h>
#include <asm/unistd.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 8, 0)
#include <linux/uaccess.h>

/* 5.8 引入 TWA_RESUME 枚举；5.4 的 task_work_add 用 bool notify，true 语义等价 */
#ifndef TWA_RESUME
#define TWA_RESUME true
#endif

/* 5.8 引入 *_nofault 系列；5.4 用 probe_kernel_* / *_inatomic 顶上 */
#define copy_to_kernel_nofault(dst, src, size)   probe_kernel_write((dst), (src), (size))
#define copy_from_kernel_nofault(dst, src, size) probe_kernel_read((dst), (src), (size))

#define copy_from_user_nofault(dst, src, size)                       \
	({                                                           \
		long __ksu_r;                                        \
		pagefault_disable();                                 \
		__ksu_r = __copy_from_user_inatomic((dst), (src), (size)); \
		pagefault_enable();                                  \
		__ksu_r;                                             \
	})

#define copy_to_user_nofault(dst, src, size)                         \
	({                                                           \
		long __ksu_r;                                        \
		pagefault_disable();                                 \
		__ksu_r = __copy_to_user_inatomic((dst), (src), (size));   \
		pagefault_enable();                                  \
		__ksu_r;                                             \
	})

/* 5.4 的 strncpy_from_user 本身就做了 pagefault 处理 */
#define strncpy_from_user_nofault(dst, src, count) strncpy_from_user((dst), (src), (count))
#endif /* < 5.8 */

#endif
