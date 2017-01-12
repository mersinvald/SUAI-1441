
Symtab for file main.c
Compilation directory is /home/mike/dev/labs/K2/OP/labOP1
Read from object file /home/mike/dev/labs/K2/OP/labOP1/lab2 (0x2933f00)
Language: c

Line table:

 line 6 at 0x400846
 line 7 at 0x400852
 line 9 at 0x400859
 line 10 at 0x400861
 line 13 at 0x400870
 line 14 at 0x400885
 line 15 at 0x400891
 line 16 at 0x4008bf
 line 17 at 0x4008e4
 line 19 at 0x4008ed
 line 20 at 0x40090b
 line 17 at 0x400930
 line 22 at 0x40093f
 line 14 at 0x400961
 line 24 at 0x400971
 line 25 at 0x400975
 line 27 at 0x40097c
 line 29 at 0x40098f
 line 30 at 0x400996
 line 32 at 0x4009b8
 line 33 at 0x4009c1
 line 34 at 0x4009e3
 line 35 at 0x4009eb
 line 36 at 0x4009f1
 line 32 at 0x4009f7
 line 39 at 0x400a03
 line 40 at 0x400a0c
 line 41 at 0x400a0f
 line 43 at 0x400a11
 line 44 at 0x400a24
 line 46 at 0x400a55
 line 47 at 0x400a60
 line 48 at 0x400a82
 line 49 at 0x400aa8
 line 50 at 0x400aaf
 line 51 at 0x400ab9
 line 53 at 0x400abb
 line 55 at 0x400ac5
 line 57 at 0x400ad4
 line 58 at 0x400ae3
 line 60 at 0x400ae5
 line 62 at 0x400af4
 line 63 at 0x400afd
 line 62 at 0x400b26
 line 65 at 0x400b32
 line 67 at 0x400b34
 line 69 at 0x400b43
 line 70 at 0x400b4c
 line 69 at 0x400b6b
 line 72 at 0x400b77
 line 73 at 0x400b83
 line 76 at 0x400b85
 line 76 at 0x400b94
 line 77 at 0x400ba3
 line 78 at 0x400baf
 line 80 at 0x400bbf
 line 81 at 0x400bd5
 line 83 at 0x400be6
 line 86 at 0x400bf4
 line 88 at 0x400c0c
 line 89 at 0x400c16
 line 91 at 0x400c27
 line 93 at 0x400c3e
 line 95 at 0x400c54
 line 96 at 0x400c5e
 line 98 at 0x400c6f
 line 99 at 0x400c80
 line 100 at 0x400c85

Blockvector:

block #000, object at 0x298f080, 2 syms/buckets in 0x400846..0x400c9b
 void del(char **, int *, int); block object 0x298e430, 0x400a11..0x400ae5
 void release(char **, int); block object 0x298ea90, 0x400b34..0x400b85
 char **generate(int); block object 0x298b980, 0x400846..0x40097c
 int longest(char **, int, int *); block object 0x298dff0, 0x40097c..0x400a11
 void show(char **, int); block object 0x298e760, 0x400ae5..0x400b34
 int main(int, char **); block object 0x298ef70, 0x400b85..0x400c9b section .text
  block #001, object at 0x298f000 under 0x298f080, 3 syms/buckets in 0x400846..0x400c9b
   typedef unsigned char unsigned char; 
   typedef signed char signed char; 
   typedef long int long int; 
   typedef sizetype sizetype; 
   typedef short unsigned int short unsigned int; 
   typedef unsigned int unsigned int; 
   typedef short int short int; 
   typedef long unsigned int long unsigned int; 
   typedef int int; 
   typedef char char; 
   typedef long long int long long int; 
   typedef unsigned int uint; 
   typedef long long unsigned int long long unsigned int; 
    block #002, object at 0x298b980 under 0x298f000, 7 syms/buckets in 0x400846..0x40097c, function generate
     int size; computed at runtime
     int lenght; computed at runtime
     char *dict; computed at runtime
     int dictlen; computed at runtime
     int i; computed at runtime
     int j; computed at runtime
     char **array; computed at runtime
      block #003, object at 0x298b910 under 0x298b980, 1 syms/buckets in 0x4008ed..0x400930
       char random; computed at runtime
    block #004, object at 0x298dff0 under 0x298f000, 6 syms/buckets in 0x40097c..0x400a11, function longest
     char **array; computed at runtime
     int size; computed at runtime
     int *lenght; computed at runtime
     int i; computed at runtime
     int max_id; computed at runtime
     int max; computed at runtime
      block #005, object at 0x298df80 under 0x298dff0, 1 syms/buckets in 0x4009c1..0x4009f7
       int clen; computed at runtime
    block #006, object at 0x298e430 under 0x298f000, 3 syms/buckets in 0x400a11..0x400ae5, function del
     char **array; computed at runtime
     int *size; computed at runtime
     int row; computed at runtime
      block #007, object at 0x298e3c0 under 0x298e430, 1 syms/buckets in 0x400a60..0x400ac3
       char **new_arr; computed at runtime
    block #008, object at 0x298e760 under 0x298f000, 3 syms/buckets in 0x400ae5..0x400b34, function show
     char **array; computed at runtime
     int size; computed at runtime
     unsigned int i; computed at runtime
    block #009, object at 0x298ea90 under 0x298f000, 3 syms/buckets in 0x400b34..0x400b85, function release
     char **array; computed at runtime
     int size; computed at runtime
     int i; computed at runtime
    block #010, object at 0x298ef70 under 0x298f000, 6 syms/buckets in 0x400b85..0x400c9b, function main
     int argc; computed at runtime
     char **argv; computed at runtime
     int size; computed at runtime
     char **array; computed at runtime
     int l_len; computed at runtime
     int l_id; computed at runtime


Symtab for file /usr/include/sys/types.h
Compilation directory is /home/mike/dev/labs/K2/OP/labOP1
Read from object file /home/mike/dev/labs/K2/OP/labOP1/lab2 (0x2933f00)
Language: c

Blockvector same as previous symtab

