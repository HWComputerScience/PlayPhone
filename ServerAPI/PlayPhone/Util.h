//
//  Util.h
//  ServerXcode
//
//  Created by James Lennon on 11/4/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#ifndef __ServerXcode__Util__
#define __ServerXcode__Util__

#include <stdio.h>
#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);

std::string fileToBase64(std::string filePath);

#endif /* defined(__ServerXcode__Util__) */
