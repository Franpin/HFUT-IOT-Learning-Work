#include "stdio.h"
#define GPKCON0 (*(volatile unsigned long *)0x7F008800)
#define GPKDAT (*(volatile unsigned long *)0x7F008808)
#define		PWMTIMER_BASE			(0x7F006000)
#define		TCFG0    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x00)) )
#define		TCFG1    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x04)) )
#define		TCON      	( *((volatile unsigned long *)(PWMTIMER_BASE+0x08)) )
#define		TCNTB0    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x0C)) )
#define		TCMPB0    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x10)) )
#define		TCNTO0    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x14)) )
#define		TCNTB1    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x18)) )
#define		TCMPB1    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x1C)) )
#define		TCNTO1    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x20)) )
#define		TCNTB2    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x24)) )
#define		TCMPB2    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x28)) )
#define		TCNTO2    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x2C)) )
#define		TCNTB3    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x30)) )
#define		TCMPB3    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x34)) )
#define		TCNTO3    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x38)) )
#define		TCNTB4    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x3C)) )
#define		TCNTO4    	( *((volatile unsigned long *)(PWMTIMER_BASE+0x40)) )
#define		TINT_CSTAT 	( *((volatile unsigned long *)(PWMTIMER_BASE+0x44)) )
#define GPNCON (*(volatile unsigned long *)0x7F008830)
#define GPNDAT (*(volatile unsigned long *)0x7F008834)
#define GPFCON (*(volatile unsigned int *)0x7F0080A0)
#define GPFDAT (*(volatile unsigned int *)0x7F0080A4)
#define VIC0ADDRESS (*((volatile unsigned long *)0x71200f00))
#define TINT_CSTAT ( *((volatile unsigned long *)(PWMTIMER_BASE+0x44)) )
void timer_init(unsigned long utimer,unsigned long uprescaler,unsigned long udivider,unsigned long utcntb,unsigned long utcmpb);

unsigned long reset;
void buzzer_on()
{	
	int dat = 0;
	int i=0;//初始化计数值
	int k=1000;//初始化报警值
	// 配置GPK4-7为输出功能
	GPKCON0 = 0x11110000;	
	
	// 所有LED熄灭
	GPKDAT = 0x000000f0;
	
	// 配置GPN为输入功能
	GPNCON = 0;
	// 轮询的方式查询按键事件
	while(1)
	{
		
		dat = GPNDAT;
		if(!(dat & (1<<0))){//当按下K1时
			while(1){//进入死循环
				dat = GPNDAT;
				if(dat & (1<<0)){//等K1松开，循环才结束
					break;
				}
			}
			i++;//计数器值加1
			//GPKDAT =0x00000000;
		}	
		if(!(dat & (1<<1))){//按下K2
			k=5;//设置报警值为5
		}
		if(!(dat & (1<<2))){//按下K3
			k=10;//设置报警值为10
		}
		if(i==k){//计数值等于报警值时
			timer_init(0,65,4,62500*0.5,0);//定时器初始化，开始调用
		}
		if(!(dat & (1<<3))){
			buzzer_off();//关闭蜂鸣器
			dat = 0;
			i=0;//重新设置计数值
			k=1000;//重新设置报警值
			// 配置GPN为输入功能
			GPNCON = 0;
			flag=0;
			GPKDAT =0x000000f0;
			TINT_CSTAT=reset;//关闭定时中断
		}
		//GPKDAT =0x000000f0;
	}

}
void buzzer_off()
{
	GPFDAT &= ~(1<<14);
}

void buzzer_init(void)
{
	// set GPF14 as output
	GPFCON |= 1<<28;
	GPFCON &= ~(1<<29);
}


int main()
{
	reset=TINT_CSTAT;//保存最开始的中断状态
	buzzer_init();//蜂鸣器初始化
	while (1)
	{
		buzzer_on();//进入蜂鸣器函数
		break;
	}
	
	return 0;
}
