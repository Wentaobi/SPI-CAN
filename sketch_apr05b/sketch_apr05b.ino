// 1st CAN Network - CAN TRANSMIT

#include <mcp_can.h>
#include <SPI.h>


const int SPI_CS_PIN = 10;

// Build an ID or PGN

//long unsigned int txID = 0x88; // This format is typical of a 29 bit identifier.. the most significant digit is never greater than one.
unsigned int txID = 0x88; // This format is typical of a 29 bit identifier.. the most significant digit is never greater than one.

// unsigned char stmp[8] = {0xEE, 0x00, 0xFF, 0x22, 0xE9, 0xFA, 0xDD, 0x51};
int i = 0;
unsigned int stmp[8] = {i, i, i, i, i, i, i, i};
//Construct a MCP_CAN Object and set Chip Select to 10.

MCP_CAN CAN(SPI_CS_PIN);                            


void setup()
{
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 250K
    {
         Serial.println("CAN BUS Module Failed to Initialized");
        Serial.println("Retrying....");
        delay(200);
        
    }
    Serial.println("CAN BUS Shield init ok!");
    
}


void loop()
{   //Serial.println(CAN.checkError());
    Serial.println(CAN.mcp2515_readRegister(MCP_EFLG));
    

    // send the data:  id = 0x00, Extended Frame, data len = 8, stmp: data buf
    // Extended Frame = 1.
    
    i++;
    if(i > 99)
    {
      i = 0;
    }
    i = char(i);
    unsigned char stmp[8] = {i, i, i, i, i, i, i, i};
    CAN.sendMsgBuf(txID,0, 8, stmp);    
    delay(25);    // send data every 25mS
}

