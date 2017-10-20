#include<stdio.h>

#define FRAME_BYTE_FST 0xca
#define FRAME_BYTE_SEC 0xac
#define FRAME_BYTE_LST 0xcc
#define FRAME_HEAD_FLAG 0x80
#define FRAME_OVER_FLAG 0x40
#define BUFFER_SIZE 100

unsigned char SumCheck(void);
void FrameGet(unsigned char data);

unsigned char rec_data[BUFFER_SIZE];
unsigned char rec_index = 0x00;
unsigned char rec_flag = 0x00;

unsigned char textdata[24] = {0xca, 0xac, 0x42, 0x16, 0x01, 0x00, 0x02, 0x00, 0x03, 0x00, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0xa0, 0x40, 0x00,  0x40, 0xfe, 0xcc};

void main(void)
{
    for (i = 0; i < 24; i++)
    {
        FrameGet(textdata[i]);
    }
    if (SumCheck() == 0xfe)
    {
        printf("ok!!!!!sum");
    }
    while(1);
}

unsigned char SumCheck(void)
{
	unsigned char i = 0;
	unsigned int sum_byte = 0x00;

	for (i = 0; i < rec_data[1] - 2; i++)
	{
		sum_byte += rec_data[i];
	}

	if ((sum_byte % 256) == rec_data[rec_data[1] - 2])
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void FrameGet(unsigned char data)
{

	if (data == FRAME_BYTE_FST)
	{
		rec_flag = rec_flag | FRAME_HEAD_FLAG;

		rec_data[rec_index] = data;
		rec_index++;
	}
	else if (data == FRAME_BYTE_SEC)
	{
		if (rec_flag & FRAME_HEAD_FLAG)
		{
			rec_flag = rec_flag & ~FRAME_OVER_FLAG;

			rec_index = 0;
		}
		else
		{
			rec_data[rec_index] = data;
			rec_index++;
			rec_flag = rec_flag & ~FRAME_HEAD_FLAG;

		}
	}
	else
	{
		rec_data[rec_index] = data;
		rec_index++;
		if (rec_index == rec_data[1])
		{

			rec_flag |= FRAME_OVER_FLAG;

            for (j = 0; j < rec_data[1]; j++)
            {
                printf("µÚ%d¸öÊý¾ÝÊÇ£º%x \n", j, rec_data[j]);
            }

		}
	}

	if (rec_index == BUFFER_SIZE)
	{
		rec_index--;
	}



}

