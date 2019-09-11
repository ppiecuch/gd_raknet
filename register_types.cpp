#include "register_types.h"
#include "RakNetExample.h"

void register_gd_raknet_types()
{
		ClassDB::register_class<RakNetExample>();
}

void unregister_gd_raknet_types() {
   //nothing to do here
}
