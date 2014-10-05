#ifndef _kick_config_h
#define _kick_config_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

#ifndef KICK_POLYMORPHIC
#define KICK_POLYMORPHIC 1
#endif

#ifndef KICK_POLYMORPHIC_CONTAINERS
#define KICK_POLYMORPHIC_CONTAINERS KICK_POLYMORPHIC
#endif

#ifndef KICK_POLYMORPHIC_IO
#define KICK_POLYMORPHIC_IO KICK_POLYMORPHIC
#endif

namespace kick {
	typedef int size_type;
	typedef unsigned int size_t;
	
}

#endif // _kick_config_h
