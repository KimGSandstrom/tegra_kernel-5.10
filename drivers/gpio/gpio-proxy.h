#ifndef GPIO_PROXY_H
#define GPIO_PROXY_H

#ifdef GPIO_DEBUG
#ifndef deb_debug
#define deb_debug(fmt, ...)    printk(KERN_DEBUG "GPIO func \'%s\' -- " fmt, __func__, ##__VA_ARGS__)
#endif
#endif
#ifdef GPIO_deb_verbose
#ifndef deb_verbose
#define deb_verbose            deb_debug
#endif
#endif

/* passthrough hooks for low level functions such as readl and writel
 * functions are mainly intended for GPIO passthrough
 */

extern bool kernel_is_on_guest;

extern inline u32 readl_redirect( void * addr, unsigned char type);
extern inline void writel_redirect( u32 value, void * addr, unsigned char type);
extern void __iomem *tegra186_gpio_get_base_redirect(unsigned char id, unsigned int pin);

extern const unsigned char rwl_std_type;
extern const unsigned char rwl_raw_type;
extern const unsigned char rwl_relaxed_type;

#if defined(CONFIG_TEGRA_GPIO_GUEST_PROXY) || defined(CONFIG_TEGRA_GPIO_HOST_PROXY)

static inline u32 readl_both_local( void * addr) {
  u32 ret, ret_l;
  deb_verbose("\n");
  ret_l = readl(addr);
  if(kernel_is_on_guest) {
    ret = readl_redirect(addr, rwl_std_type);
  }
  if( ret_l != ret ) deb_debug("return values differ %d/%d", ret_l , ret);
  return ret_l; 
}

static inline u32 readl_both( void * addr) {
  u32 ret, ret_l;
  deb_verbose("\n");
  ret_l = readl(addr);
  if(kernel_is_on_guest) {
    ret = readl_redirect(addr, rwl_std_type);
  }
  if( ret_l != ret ) deb_debug("return values differ %d/%d", ret_l , ret);
  return ret; 
}

static inline void writel_both( u32 value, void * addr) {
  deb_verbose("\n");
  writel(value, addr);
  if(kernel_is_on_guest) {
    writel_redirect(value, addr, rwl_std_type);
  }
};

static inline u32 __raw_readl_both( void * addr) {
  u32 ret, ret_l;
  deb_verbose("\n");
  ret_l = __raw_readl(addr);
  if(kernel_is_on_guest) {
    ret = readl_redirect(addr, rwl_raw_type);
  }
  if( ret_l != ret ) deb_debug("return values differ %d/%d", ret_l , ret);
  return ret; 
};

static inline void __raw_writel_both( u32 value, void * addr) {
  deb_verbose("\n");
  __raw_writel(value, addr);
  if(kernel_is_on_guest) {
    writel_redirect(value, addr, rwl_raw_type);
  }
};

static inline u32 readl_relaxed_both( void * addr) {
  u32 ret, ret_l;
  deb_verbose("\n");
  ret_l = readl_relaxed(addr);
  if(kernel_is_on_guest) {
    ret = readl_redirect(addr, rwl_relaxed_type);
  }
  if( ret_l != ret ) deb_debug("return values differ %d/%d", ret_l , ret);
  return ret; 
};

static inline void writel_relaxed_both( u32 value, void * addr) {
  deb_verbose("\n");
  writel_relaxed(value, addr);
  if(kernel_is_on_guest) {
    writel_redirect(value, addr, rwl_relaxed_type);
  }
};

static inline u32 readl_x( void * addr) {
  u32 ret;
  deb_verbose("\n");
  if(kernel_is_on_guest) {
    ret = readl_redirect(addr, rwl_std_type);
  }
  else {
    ret = readl(addr);
  }
  return ret; 
};

static inline void writel_x( u32 value, void * addr) {
  deb_verbose("\n");
  if(kernel_is_on_guest) {
    writel_redirect(value, addr, rwl_std_type);
  }
  else {
    writel(value, addr);
  }
};

static inline u32 __raw_readl_x( void * addr) {
  u32 ret;
  deb_verbose("\n");
  if(kernel_is_on_guest) {
    ret = readl_redirect(addr, rwl_raw_type);
  }
  else {
    ret = __raw_readl(addr);
  }
  return ret; 
};

static inline void __raw_writel_x( u32 value, void * addr) {
  deb_verbose("\n");
  if(kernel_is_on_guest) {
    writel_redirect(value, addr, rwl_raw_type);
  }
  else {
    __raw_writel(value, addr);
  }
};

static inline u32 readl_relaxed_x( void * addr) {
  u32 ret;
  deb_verbose("\n");
  if(kernel_is_on_guest) {
    ret = readl_redirect(addr, rwl_relaxed_type);
  }
  else {
    ret = readl_relaxed(addr);
  }
  return ret; 
};

static inline void writel_relaxed_x( u32 value, void * addr) {
  deb_verbose("\n");
  if(kernel_is_on_guest) {
    writel_redirect(value, addr, rwl_relaxed_type);
  }
  else {
    writel_relaxed(value, addr);
  }
};

// these passthroughs are not necessary because the functions above are called in the passthrough version of this code
/*
static inline u32 pmx_readl( void * addr) { return 0; };
static inline void pmx_writel( u32 value, void * addr) {};
static inline u32 tegra_gpio_readl( void * addr) { return 0;};
static inline void tegra_gpio_writel( u32 value, void * addr) {};
static inline u32 tegra_gte_readl( void * addr) { return 0; };
static inline void tegra_gte_writel( u32 value, void * addr) {};
*/
// note: adding more higher level functions migth take latency off the lower level functions
#else

static inline u32 readl_x( void * addr) {
    return readl(addr);
};

static inline void writel_x( u32 value, void * addr) {
    writel(value, addr);
};

static inline u32 __raw_readl_x( void * addr) {
    return __raw_readl(addr);
};

static inliae void __raw_writel_x( u32 value, void * addr) {
    __raw_writel(value, addr);
};

static inline u32 readl_relaxed_x( void * addr) {
    return readl_relaxed(addr);
};

static inline void writel_relaxed_x( u32 value, void * addr) {
    writel_relaxed(value, addr);
};
#endif

#endif
