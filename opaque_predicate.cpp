#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{ // semantic: a=2;b=5;c=220;d=332;e=434234;return (a*b+c-d*(e*e));
	int fd = open("/dev/urandom",O_RDWR);
	long a,b,c,d,e;
	long x;
	long y;
	long z;
	read(fd,&x,8);
	if(3*(x*x*x)+25*x-6 < 0)
	{
		read(fd,&y,8);
		if(((~(y << 5)^0x43423df)&0x46)%3)
		{
			printf("in 1 block\n");
			a = 0x01<<1;
			b = (0x01<<2)|0x01;
			c = ((0xfffffff7^0xffffffff)<<2) | 192;
			c-=4;
			d = (1<<7)^460;
			e = 0xdf7623-(0xac970a05^0xac4fdfec);

			long e_next = e;
			for(int i = 0;i < e-1;i++) e_next+=e;
			printf("result: %ld\n",a*b+c-(d*e_next));
			return a*b+c-(d*e_next);
		}
		else 
		{
			printf("in 2 block\n");
			a = (3442794271^0xcd34df1a)-3;
			b = (57248948^0x434123)&4;
			b++;
			c = 988 & 255;
			d = (203|260) & 332;
			e = (11627287 + 3407820) ^ 0xdfcae5;
			long el,tmp;
			
			for (int i = 16;i >= 0 ;i -= 8) 
			{
				el = e & 0xff;
				el <<= i;
				tmp |= el;
				e >>= 0x08;
			}
			e = tmp*tmp;
			printf("result: %ld\n",a*b+c-(d*e));
			return a*b+c-(d*e);
		}
	}
	else 
	{
		read(fd,&z,8);
		if(((((z^0xffd6) >> 2) | 0xac0000000000) % 2)) 
		{
			printf("in 3 block\n");
			c = 400 ^ ((203|260) & 332);
			a = c / (145^255);
			b = 20 / (((63255150 ^ 0xacbeda)^0x434123)&4);
			d = (((0451/8)%8)<<6) | ((0451%8)<<3) | (((0451/8)/8)%8);
			e = (d+(4443635 ^ 0x69eee)-4109359)*((b-~((294333+102190) ^ 0xacde))-1);

			printf("result: %ld\n",a*b+c-(d*e));
			return a*b+c-(d*e);
		}
		else 
		{
			printf("in 4 block\n");
			a = (~-2)+1;
			b = 25/5;
			c = ((103+81)^0xac) + (((((42+056)/8)%8) << 6) | (((0xace^(542*5))/8/8)%8 << 3) | (0xff^0xfe)-1);
			d = 07252432454235332;
			long tmp1 = 0;
			for(int i = 0;i < 16;i++) 
			{
				tmp1 += d % 8;
				d /= 8;
			}
			
			long tmp2 = 9539649576;
			long tmp3 = 0;
			long tmp4 = (16116873 + 234343) ^ 0xffdfca;
			for (int i = 0;i < 3;i++)
			{
				if(i%10 == 2) tmp4 *= tmp4;
				for(int j = 0;j < 10;j++) 
				{
					tmp3 += tmp2 % 10;
					tmp2 /= 10;
				}
			}

			printf("result: %ld\n",b*a+c-((157+tmp3+tmp1+tmp1)*(tmp4)));			
			return b*a+c-((157+tmp3+tmp1+tmp1)*(tmp4));
			
		}
	}
}
