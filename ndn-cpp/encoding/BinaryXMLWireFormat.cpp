/**
 * @author: Jeff Thompson
 * See COPYING for copyright and distribution information.
 */

#include <stdexcept>
#include "../c/encoding/BinaryXMLName.h"
#include "../c/encoding/BinaryXMLInterest.h"
#include "../Interest.hpp"
#include "BinaryXMLEncoder.hpp"
#include "../c/encoding/BinaryXMLDecoder.h"
#include "BinaryXMLWireFormat.hpp"

using namespace std;

namespace ndn {

BinaryXMLWireFormat BinaryXMLWireFormat::instance_;

void BinaryXMLWireFormat::encodeName(const Name &name, vector<unsigned char> &output) 
{
  struct ndn_Name nameStruct;
  struct ndn_NameComponent components[100];
  ndn_Name_init(&nameStruct, components, sizeof(components) / sizeof(components[0]));
  name.get(nameStruct);

  BinaryXMLEncoder encoder;
  ndn_encodeBinaryXMLName(&nameStruct, encoder.getEncoder());
     
  encoder.appendTo(output);
}

void BinaryXMLWireFormat::decodeName(Name &name, const unsigned char *input, unsigned int inputLength)
{
  struct ndn_NameComponent components[100];
  struct ndn_Name nameStruct;
  ndn_Name_init(&nameStruct, components, sizeof(components) / sizeof(components[0]));
    
  struct ndn_BinaryXMLDecoder decoder;
  ndn_BinaryXMLDecoder_init(&decoder, (unsigned char *)input, inputLength);
  
  ndn_Error error;
  if (error = ndn_decodeBinaryXMLName(&nameStruct, &decoder))
    throw std::runtime_error(ndn_getErrorString(error));

  name.set(nameStruct);
}

void BinaryXMLWireFormat::encodeInterest(const Interest &interest, vector<unsigned char> &output) 
{
  struct ndn_Interest interestStruct;
  struct ndn_NameComponent components[100];
  ndn_Interest_init(&interestStruct, components, sizeof(components) / sizeof(components[0]));
  interest.get(interestStruct);

  BinaryXMLEncoder encoder;
  ndn_encodeBinaryXMLInterest(&interestStruct, encoder.getEncoder());
     
  encoder.appendTo(output);
}

void BinaryXMLWireFormat::decodeInterest(Interest &interest, const unsigned char *input, unsigned int inputLength)
{
  struct ndn_NameComponent components[100];
  struct ndn_Interest interestStruct;
  ndn_Interest_init(&interestStruct, components, sizeof(components) / sizeof(components[0]));
    
  struct ndn_BinaryXMLDecoder decoder;
  ndn_BinaryXMLDecoder_init(&decoder, (unsigned char *)input, inputLength);
  
  ndn_Error error;
  if (error = ndn_decodeBinaryXMLInterest(&interestStruct, &decoder))
    throw std::runtime_error(ndn_getErrorString(error));

  interest.set(interestStruct);
}

}
