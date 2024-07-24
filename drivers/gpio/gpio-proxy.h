#ifndef GPIO_PROXY_H
#define GPIO_PROXY_H

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

// TODO
// check readl_x() and writel_x() in files: gpio-tegra.c, pinctrl-tegra.c

static inline u32 readl_x( void * addr) {
  u32 ret;
  if(kernel_is_on_guest) {
    ret = readl_redirect(addr, rwl_std_type);
  }
  else {
    ret = readl(addr);
  }
  return ret;  
};

static inline void writel_x( u32 value, void * addr) {
  if(kernel_is_on_guest) {
    writel_redirect(value, addr, rwl_std_type);
  }
  else {
    writel(value, addr);
  }
};

static inline u32 __raw_readl_x( void * addr) {
  u32 ret;
  if(kernel_is_on_guest) {
    ret = readl_redirect(addr, rwl_raw_type);
  }
  else {
    ret = __raw_readl(addr);
  }
  return ret;  
};

static inline void __raw_writel_x( u32 value, void * addr) {
  if(kernel_is_on_guest) {
    writel_redirect(value, addr, rwl_raw_type);
  }
  else {
    __raw_writel(value, addr);
  }
};

static inline u32 readl_relaxed_x( void * addr) {
  u32 ret;
  if(kernel_is_on_guest) {
    ret = readl_redirect(addr, rwl_relaxed_type);
  }
  else {
    ret = readl_relaxed(addr);
  }
  return ret;  
};

static inline void writel_relaxed_x( u32 value, void * addr) {
  if(kernel_is_on_guest) {
    writel_redirect(value, addr, rwl_relaxed_type);
  }
  else {
    writel_relaxed(value, addr);
  }
};


// TODO, adding these passthroughs would make execution less latent
/*
static inline u32 pmx_readl_x( void * addr) { return 0; };
static inline void pmx_writel_x( u32 value, void * addr) {};
static inline u32 tegra_gpio_readl_x( void * addr) { return 0;};
static inline void tegra_gpio_writel_x( u32 value, void * addr) {};
static inline u32 tegra_gte_readl_x( void * addr) { return 0; };
static inline void tegra_gte_writel_x( u32 value, void * addr) {};
*/
// note: adding more higher level functions migth take latency off the lower level functions

#endif
