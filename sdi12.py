#!/usr/local/opt/python-3.5.1/bin/python3.5
# SDI-12 Sensor Data Logger Copyright Dr. John Liu 2016-04-18
import serial.tools.list_ports
import serial
import time
import datetime
import re
import os
import platform
import urllib.parse
 
public_key='0lzK7vGNXoiygzGlZbrY' # Apply for your data stream at https://data.sparkfun.com/ This stream is shared among everyone running this sample code
private_key='D6nYzAN4PwCJpvGb81nE'
curl_command_format='curl -X GET "http://data.sparkfun.com/input/%s?private_key=%s&unit_id=%s%s"' # This is the cURL upload command to sparkfun's phant server
unit_id=platform.node() # Use computer name as unit_id. For a raspberry pi, change its name from raspberrypi to something else to avoid confusion
curl_exists=False # The code will test whether cURL exists. If it exists, it will be used to upload data.
if (os.system('curl -V')==0):
    curl_exists=True
 
print('+-'*40)
print('SDI-12 Sensor Python Data Logger with Telemetry V1.1')
print('Designed for Dr. Liu\'s SDI-12 USB adapter\n\tDr. John Liu Saint Cloud MN USA 2016-04-18 V1.1\n\t\tFree software GNU GPL V3.0')
print('\nCompatible with Windows, Linux, Mac OSX, and Raspberry PI')
print('\nThis program requires Python 3.5, Pyserial 3.0, and cURL (data upload)')
print('\nData is logged to YYYYMMDD.CVS in the Python code\' folder')
print('\nVisit https://data.sparkfun.com/streams/0lzK7vGNXoiygzGlZbrY/ to retrived uploaded data')
print('\nIf multiple people are running this code, they are distinguished by unit_id, although all raspberry pis have the same "raspberrypi" unit_id.')
print ('\nFor assistance with customization, telemetry etc., contact Dr. Liu.\n\thttps://liudr.wordpress.com/gadget/sdi-12-usb-adapter/')
print('+-'*40)
 
port_names=[]
a=serial.tools.list_ports.comports()
for w in a:
    port_names.append(w.device)
  
port_names.sort()
print('\nDetected the following serial ports:')
i=0
for w in port_names:
    print('%d) %s' %(i,w))
    i=i+1
total_ports=i # now i= total ports
 
user_port_selection=input('\nSelect port: (0,1,2...)')
if (int(user_port_selection)>=total_ports):
    exit(1) # port selection out of range
 
ser=serial.Serial(port=port_names[int(user_port_selection)],baudrate=9600,timeout=10)
time.sleep(2.5) # delay for arduino bootloader and the 1 second delay of the adapter.
 
total_data_count=int(input('Total number of data points:'))
delay_between_pts=int(input('Delay between data points (second):'))
 
print('Time stamps are generated with:\n0) GMT/UTC\n1) Local\n')
time_zone_choice=int(input('Select time zone.'))
 
if time_zone_choice==0:
    now=datetime.datetime.utcnow() # use UTC time instead of local time
elif time_zone_choice==1:
    now=datetime.datetime.now() # use local time, not recommended for multiple data loggers in different time zones
     
data_file_name="%04d%02d%02d.csv" %(now.year,now.month,now.day)
data_file = open(data_file_name, 'a') # open yyyymmdd.csv for appending
 
sdi_12_address=b'z'
user_sdi_12_address=input('SDI-12 sensor address: (0-9, A-Z, a-z)')
if ((user_sdi_12_address>='0') and (user_sdi_12_address<='9')) or ((user_sdi_12_address>='A') and (user_sdi_12_address<='Z')) or ((user_sdi_12_address>='a') and (user_sdi_12_address<='z')):
    sdi_12_address=user_sdi_12_address.encode('utf-8')
    print("Using address: ", user_sdi_12_address)
else:
    print('Address is invalid. Using default address: z')
print('Saving to %s' %data_file_name)
 
ser.write(sdi_12_address+b'I!')
sdi_12_line=ser.readline()
print('Sensor info:',sdi_12_line.decode('utf-8'))
 
values=[]
for j in range(total_data_count):
    ser.write(sdi_12_address+b'M!'); # start the measurement
    sdi_12_line=ser.readline()
    sdi_12_line=sdi_12_line[:-2] # remove \r and \n since [0-9]$ has trouble with \r
    m=re.search(b'[0-9]$',sdi_12_line) # having trouble with the \r
    total_returned_values=int(m.group(0)) # find how many values are returned
    sdi_12_line=ser.readline() # read the service request line
    ser.write(sdi_12_address+b'D0!') # request data
    sdi_12_line=ser.readline() # read the data line
    sdi_12_line=sdi_12_line[1:-2] # remove address, \r and \n since [0-9]$ has trouble with \r
 
    if time_zone_choice==0:
        now=datetime.datetime.utcnow()
    elif time_zone_choice==1:
        now=datetime.datetime.now()
 
    for i in range(total_returned_values):
        m=re.search(b'[+-][0-9.]+',sdi_12_line) # match a number string
        values.append(float(m.group(0))) # convert into a number
        sdi_12_line=sdi_12_line[len(m.group(0)):]
 
    output_str="%04d/%02d/%02d %02d:%02d:%02d%s,%s" %(now.year,now.month,now.day,now.hour,now.minute,now.second,' GMT' if time_zone_choice==0 else '',sdi_12_address.decode('utf-8')) # formatting date and time
    i=0
    value_str='' # This stores &value0=xxx&value1=xxx&value2=xxx&value3=xxx&value4=xxx&value5=xxx
    for value_i in values:
        output_str=output_str+",%s" %(value_i) # Output returned values
        if (i<6):
            value_str=value_str+"&value%d=%s" %(i,value_i) # format values for posting to data.sparkfun.com
        i=i+1
    while (i<6):
        value_str=value_str+"&value%d=0" %(i) # format values for posting to data.sparkfun.com
        i=i+1
   
    print(output_str)
    output_str=output_str+'\n'
    data_file.write(output_str)
    if (curl_exists==True):
        curl_command=curl_command_format %(public_key,private_key,urllib.parse.quote(unit_id),value_str) # Format cURL command
        print(curl_command) # Debug information
        print(os.system(curl_command)) # Send data to data.sparkfun.com using cURL
         
    values=[] # clear values for the next iteration, 3.2.3 doesn't support clear as 3.4.3 and 3.5.1 does
    data_file.flush() # make sure data is written to the disk so stopping the scrit with ctrl - C will not cause data loss
    time.sleep(delay_between_pts)
ser.close()
data_file.close()