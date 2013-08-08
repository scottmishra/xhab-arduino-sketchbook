#ifndef _ROS_learning_actionlib_FibonacciFeedback_h
#define _ROS_learning_actionlib_FibonacciFeedback_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace learning_actionlib
{

  class FibonacciFeedback : public ros::Msg
  {
    public:
      uint8_t sequence_length;
      int32_t st_sequence;
      int32_t * sequence;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset++) = sequence_length;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      for( uint8_t i = 0; i < sequence_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_sequencei;
      u_sequencei.real = this->sequence[i];
      *(outbuffer + offset + 0) = (u_sequencei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sequencei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sequencei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sequencei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->sequence[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint8_t sequence_lengthT = *(inbuffer + offset++);
      if(sequence_lengthT > sequence_length)
        this->sequence = (int32_t*)realloc(this->sequence, sequence_lengthT * sizeof(int32_t));
      offset += 3;
      sequence_length = sequence_lengthT;
      for( uint8_t i = 0; i < sequence_length; i++){
      union {
        int32_t real;
        uint32_t base;
      } u_st_sequence;
      u_st_sequence.base = 0;
      u_st_sequence.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_sequence.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_sequence.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_sequence.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_sequence = u_st_sequence.real;
      offset += sizeof(this->st_sequence);
        memcpy( &(this->sequence[i]), &(this->st_sequence), sizeof(int32_t));
      }
     return offset;
    }

    const char * getType(){ return "learning_actionlib/FibonacciFeedback"; };
    const char * getMD5(){ return "b81e37d2a31925a0e8ae261a8699cb79"; };

  };

}
#endif