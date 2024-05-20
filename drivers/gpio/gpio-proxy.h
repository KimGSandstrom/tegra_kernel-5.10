#ifndef GPIO_PROXY_H
#define GPIO_PROXY_H

/* passthrough hooks for low level functions sudh as readl adnn writel
 * functions are mainly intended for GPIO passthrough
 */

  extern bool kernel_is_on_guest;
  extern inline u32 readl_redirect( void * addr);
  extern inline void writel_redirect( u32 value, void * addr);

  static inline u32 readl_x( void * addr) {
    u32 ret;
    if(kernel_is_on_guest) {
      deb_verbose("on guest");
      ret = readl_redirect(addr);
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
      writel_redirect(value, addr);
    }
    else {
      deb_verbose("on host");
      writel(value, addr);
    }
  };

#endif
