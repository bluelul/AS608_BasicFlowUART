/////////////////////////////////
//   FINGERPRINT SENSOR AS608  //
//    COMMUNICATION VIA UART   //
//			  bluelul          //
//          24/01/2021         //
/////////////////////////////////

/******** DEFAULT VALUES **********
   baudrate: 57600
   address:  FF FF FF FF
   password: 00 00 00 00
**********************************/

/*************** MESSAGE STRUCTURE *************************
   [prefix] [address] [tx/rx] [command] [arg] [checksum]
   
   prefix   (2 bytes): EF 01
   address  (4 bytes)
   tx/rx    (1 byte) : 01 - tx, 07 - rx
   command  (2 bytes)
   arg      (depend command)
   checksum (2 bytes): sum all bytes after [address]
***********************************************************/

//////////////////////////////////////////////////////////////
//--------- BASIC FLOW WITH PRE-ENROLLED DATABASE ----------//
//////////////////////////////////////////////////////////////

// verify password
Write data
EF 01 FF FF FF FF 01 00 07 13 00 00 00 00 00 1B
Read data
EF 01 FF FF FF FF 07 00 03 [00] 00 0A // OK

// get image (polling manually until got OK)
Write data
EF 01 FF FF FF FF 01 00 03 01 00 05
Read data
EF 01 FF FF FF FF 07 00 03 [00] 00 0A // OK

// analyze image and save to slot 1 buffer
Write data
EF 01 FF FF FF FF 01 00 04 02 01 00 08
Read data
EF 01 FF FF FF FF 07 00 03 [00] 00 0A // OK

// search slot 1 with database
Write data
EF 01 FF FF FF FF 01 00 08 04 01 00 00 [00 0A] 00 18 // [length of database]
Read data
EF 01 FF FF FF FF 07 00 07 [00] [00 01] [00 38] 00 47 // [OK] [finger id match] [confidence]
