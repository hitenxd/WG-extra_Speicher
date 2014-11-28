cpu auslastung gefixxt durch:

struct timeval delay;
delay.tv_sec=1;
delay.tv_usec=0;
select(0,NULL,NULL,NULL,&delay);