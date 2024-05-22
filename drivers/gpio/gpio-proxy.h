#ifndef GPIO_PROXY_H
#define GPIO_PROXY_H

/* passthrough hooks for low level functions sudh as readl adnn writel
 * functions are mainly intended for GPIO passthrough
 */

extern bool kernel_is_on_guest;
extern inline u32 readl_redirect( void * addr, unsigned char type);
extern inline void writel_redirect( u32 value, void * addr, unsigned char type);

extern const unsigned char rwl_std_type;
extern const unsigned char rwl_raw_type;
extern const unsigned char rwl_relaxed_type;

static inline u32 readl_x( void * addr) {
  u32 ret;
  if(kernel_is_on_guest) {
    deb_verbose("on guest");
    ret = readl_redirect(addr, rwl_std_type);
  }
  else {
    deb_verbose("on host");
    ret = readl(addr);
  }
  return ret;  
};

static inline void writel_x( u32 value, void * addr) {
  if(kernel_is_on_guest) {
    deb_verbose("on guest");
    writel_redirect(value, addr, rwl_std_type);
  }
  else {
    deb_verbose("on host");
    writel(value, addr);
  }
};

static inline u32 readl_raw_x( void * addr) {
  u32 ret;
  if(kernel_is_on_guest) {
    deb_verbose("on guest");
    ret = readl_redirect(addr, rwl_raw_type);
  }
  else {
    deb_verbose("on host");
    ret = readl(addr);
  }
  return ret;  
};

static inline void writel_raw_x( u32 value, void * addr) {
  if(kernel_is_on_guest) {
    deb_verbose("on guest");
    writel_redirect(value, addr, rwl_raw_type);
  }
  else {
    deb_verbose("on host");
    writel(value, addr);
  }

};
static inline u32 readl_relaxed_x( void * addr) {
  u32 ret;
  if(kernel_is_on_guest) {
    deb_verbose("on guest");
    ret = readl_redirect(addr, rwl_relaxed_type);
  }
  else {
    deb_verbose("on host");
    ret = readl(addr);
  }
  return ret;  
};

static inline void writel_relaxed_x( u32 value, void * addr) {
  if(kernel_is_on_guest) {
    deb_verbose("on guest");
    writel_redirect(value, addr, rwl_relaxed_type);
  }
  else {
    deb_verbose("on host");
    writel(value, addr);
  }
};

#endif
