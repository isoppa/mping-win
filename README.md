# mping-win
A mping is a windows command that pings multiple hosts.

### How to use

1. Download Zip file.
2. Unzip.
3. Run.
   ```
   mping [Destination address 1] [Interval 1] [Destination address 2] [Interval 2] ... [Destination address 16] [Interval 16]
   ```

### Command Parameter 

* Destination address 1 (required)
  * 1st destination host name or IP address
* Interval 1 (optional)
  * Ping execution interval for 1st destination.
  * Unit is seconds. 
  * Default interval is 1 second.
  * *If 0 is set, no ping is performed.*
  * *Hosts in the sinet.ad.jp domain cannot be specified for less than 60 seconds.*
* Destination address 2 ... 16 (optional)  
  * 1st destination host name or IP address
* Interval 2 ... 16 (optional)
  * Ping execution interval for 1st destination.
  * Unit is seconds. 
  * Default interval is 1 second.
  * *If 0 is set, no ping is performed.*
  * *Hosts in the sinet.ad.jp domain cannot be specified for less than 60 seconds.*

### Example
```
C:\>mping 192.168.1.1 192.168.1.18 0 192.168.1.2 5 

-----------------------------------------------
  3 destinations                 (version 2.0)
-----------------------------------------------
  Thu Mar 30 12:37:24 2023
          192.168.1.1         192.168.1.18          192.168.1.2
                    0                    0                    0 <- NG out of 156
                 <1ms   *** Skip (Inf) ***                 <1ms
                 <1ms   *** Skip (Inf) ***   *** Skip (  4) ***
                 <1ms   *** Skip (Inf) ***   *** Skip (  3) ***
                 <1ms   *** Skip (Inf) ***   *** Skip (  2) ***
                 <1ms   *** Skip (Inf) ***   *** Skip (  1) ***
                 <1ms   *** Skip (Inf) ***                 <1ms
                 <1ms   *** Skip (Inf) ***   *** Skip (  4) ***
                 <1ms   *** Skip (Inf) ***   *** Skip (  3) ***
                 <1ms   *** Skip (Inf) ***   *** Skip (  2) ***
                 <1ms   *** Skip (Inf) ***   *** Skip (  1) ***
                 <1ms   *** Skip (Inf) ***                 <1ms
                 <1ms   *** Skip (Inf) ***   *** Skip (  4) ***
                 <1ms   *** Skip (Inf) ***   *** Skip (  3) ***
                 <1ms   *** Skip (Inf) ***   *** Skip (  2) ***
                 <1ms   *** Skip (Inf) ***   *** Skip (  1) ***
                 <1ms   *** Skip (Inf) ***        *** Faild ***
```
