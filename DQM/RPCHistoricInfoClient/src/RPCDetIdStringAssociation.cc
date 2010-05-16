#include "DQM/RPCHistoricInfoClient/interface/RPCDetIdStringAssociation.h"

RPCDetIdStringAssociation::RPCDetIdStringAssociation(){

  //----------loop for DETID BARREL-----------
  int region = 0;
  for(int wheel = -2; wheel <= 2;  ++wheel){
    for(unsigned int sector = 1; sector <= 12; ++sector){
      for(unsigned int station = 1; station <= 4; ++station){

	if(station == 1){

	  for(unsigned int layer = 1; layer <= 2; ++layer){
	    RPCDetId r(region, wheel,station, sector,layer,1,1);
	    RPCGeomServ RPCname(r);
	    this->fillKeyString(RPCname.name(),r.rawId());
	    this->fillKeyRawId(r.rawId(),RPCname.name());

	    RPCDetId r1(region, wheel,station, sector,layer,1,3);
	    RPCGeomServ RPCname1(r1);
	    this->fillKeyString(RPCname1.name(),r1.rawId());
	    this->fillKeyRawId(r1.rawId(),RPCname1.name());

	  }
	}
	else if (station == 2){
	  
	  for(unsigned int layer = 1; layer <= 2; ++layer){
	    if(abs(wheel) < 2){
	      if(layer == 1){
		RPCDetId r(region, wheel,station, sector,layer,1,1);
		RPCGeomServ RPCname(r);
		this->fillKeyString(RPCname.name(),r.rawId());
		this->fillKeyRawId(r.rawId(),RPCname.name());
		
		RPCDetId r1(region, wheel,station, sector,layer,1,2);
		RPCGeomServ RPCname1(r1);
		this->fillKeyString(RPCname1.name(),r1.rawId());
		this->fillKeyRawId(r1.rawId(),RPCname1.name());
		
		RPCDetId r2(region, wheel,station, sector,layer,1,3);
		RPCGeomServ RPCname2(r2);
		this->fillKeyString(RPCname2.name(),r2.rawId());
		this->fillKeyRawId(r2.rawId(),RPCname2.name());
	      }
	      else{
		RPCDetId r(region, wheel,station, sector,layer,1,1);
		RPCGeomServ RPCname(r);
		this->fillKeyString(RPCname.name(),r.rawId());
		this->fillKeyRawId(r.rawId(),RPCname.name());
		
		RPCDetId r1(region, wheel,station, sector,layer,1,3);
		RPCGeomServ RPCname1(r1);
		this->fillKeyString(RPCname1.name(),r1.rawId());
		this->fillKeyRawId(r1.rawId(),RPCname1.name());
	      }
	    }
	    else{
	      if(layer == 2){
		RPCDetId r(region, wheel,station, sector,layer,1,1);
		RPCGeomServ RPCname(r);
		this->fillKeyString(RPCname.name(),r.rawId());
		this->fillKeyRawId(r.rawId(),RPCname.name());
		
		RPCDetId r1(region, wheel,station, sector,layer,1,2);
		RPCGeomServ RPCname1(r1);
		this->fillKeyString(RPCname1.name(),r1.rawId());
		this->fillKeyRawId(r1.rawId(),RPCname1.name());
		
		RPCDetId r2(region, wheel,station, sector,layer,1,3);
		RPCGeomServ RPCname2(r2);
		this->fillKeyString(RPCname2.name(),r2.rawId());
		this->fillKeyRawId(r2.rawId(),RPCname2.name());
	      }
	      else{
		RPCDetId r(region, wheel,station, sector,layer,1,1);
		RPCGeomServ RPCname(r);
		this->fillKeyString(RPCname.name(),r.rawId());
		this->fillKeyRawId(r.rawId(),RPCname.name());
		
		RPCDetId r1(region, wheel,station, sector,layer,1,3);
		RPCGeomServ RPCname1(r1);
		this->fillKeyString(RPCname1.name(),r1.rawId());
		this->fillKeyRawId(r1.rawId(),RPCname1.name());
	      }
	    }
	  }
	}
	else if (station == 3){
	  for(unsigned int subsector = 1; subsector <= 2; ++subsector){
		RPCDetId r(region, wheel,station, sector,1,subsector,1);
		RPCGeomServ RPCname(r);
		this->fillKeyString(RPCname.name(),r.rawId());
		this->fillKeyRawId(r.rawId(),RPCname.name());
		
		RPCDetId r1(region, wheel,station, sector,1,subsector,3);
		RPCGeomServ RPCname1(r1);
		this->fillKeyString(RPCname1.name(),r1.rawId());
		this->fillKeyRawId(r1.rawId(),RPCname1.name());
	  }
	}
	else if (station == 4){
	  for(unsigned int subsector = 1; subsector <= 4; ++subsector){

	    if(sector != 9 && sector != 11 && sector != 4 ){
	      if(subsector > 2) break;
	      RPCDetId r(region, wheel,station, sector,1,subsector,1);
	      RPCGeomServ RPCname(r);
	      this->fillKeyString(RPCname.name(),r.rawId());
	      this->fillKeyRawId(r.rawId(),RPCname.name());
	      
	      RPCDetId r1(region, wheel,station, sector,1,subsector,3);
	      RPCGeomServ RPCname1(r1);
	      this->fillKeyString(RPCname1.name(),r1.rawId());
	      this->fillKeyRawId(r1.rawId(),RPCname1.name());
	    }
	    else if (sector == 9 || sector == 11){
	      if(subsector > 1) break;
	      RPCDetId r(region, wheel,station, sector,1,subsector,1);
	      RPCGeomServ RPCname(r);
	      this->fillKeyString(RPCname.name(),r.rawId());
	      this->fillKeyRawId(r.rawId(),RPCname.name());
	      
	      RPCDetId r1(region, wheel,station, sector,1,subsector,3);
	      RPCGeomServ RPCname1(r1);
	      this->fillKeyString(RPCname1.name(),r1.rawId());
	      this->fillKeyRawId(r1.rawId(),RPCname1.name());
	    }
	    else if (sector == 4){
	      RPCDetId r(region, wheel,station, sector,1,subsector,1);
	      RPCGeomServ RPCname(r);
	      this->fillKeyString(RPCname.name(),r.rawId());
	      this->fillKeyRawId(r.rawId(),RPCname.name());
	      
	      RPCDetId r1(region, wheel,station, sector,1,subsector,3);
	      RPCGeomServ RPCname1(r1);
	      this->fillKeyString(RPCname1.name(),r1.rawId());
	      this->fillKeyRawId(r1.rawId(),RPCname1.name());
	    }
	  }
	}
      }
    }
  }

  //----------loop for DETID EndCap-----------

  for(int region = -1; region <= 1; ++region){
    if (region == 0) continue;
    for(unsigned int station = 1; station <= 3; ++station){
      for(unsigned int ring = 1; ring <= 3; ++ring){
	for(unsigned int sector = 1; sector <= 6; ++sector){
	  for(unsigned int subsector = 1; subsector <= 6; ++subsector){
	    for(unsigned int roll = 1; roll <= 3; ++roll){
	      RPCDetId r(region, ring,station, sector,1,subsector,roll);
	      RPCGeomServ RPCname(r);
	      this->fillKeyString(RPCname.name(),r.rawId());
	      this->fillKeyRawId(r.rawId(),RPCname.name());
	    }
	  }
	}
      }
    }
  }



  //----------loop for Global Plots-----------

  // region -1  ----> 1
  // region 0   ----> 2
  // region 1   ----> 3

  // wheel -2  ----> 1 
  // wheel -1  ----> 2 
  // wheel +0  ----> 3
  // wheel +1  ----> 4 
  // wheel +2  ----> 5 

  // disk -3  ----> 1 
  // disk -2  ----> 2 
  // disk -1  ----> 3
  // disk +1  ----> 4 
  // disk +2  ----> 5 
  // disk +3  ----> 6

  // Near ----> 1
  // Far ----> 2


  this->fillKeyString("RPC",1000);
  this->fillKeyRawId(1000,"RPC");


  this->fillKeyString("EndcapNegative",1);
  this->fillKeyRawId(1,"EndcapNegative");
  this->fillKeyString("Barrel",2);
  this->fillKeyRawId(2,"Barrel");
  this->fillKeyString("EndcapPositive",3);
  this->fillKeyRawId(3,"EndcapPositive");

  //Barrel
  for(int i=-2; i <= 2; i++){
    std::string name = "Wheel_"+int2string(i);

    int id = 0;
    if(i == -2) id = 21;
    if(i == -1) id = 22;
    if(i == 0) id = 23;
    if(i == 1) id = 24;
    if(i == 2) id = 25;

    this->fillKeyString(name,id);
    this->fillKeyRawId(id,name);
    this->fillKeyString(name+"near",id*10+1);
    this->fillKeyRawId(id*10+1,name+"near");
    this->fillKeyString(name+"far",id*10+2);
    this->fillKeyRawId(id*10+2,name+"far");

  }

  //Endcap 
  for(int i=-3; i <= 3; i++){
    if(i == 0 ) continue;
    std::string name = "Disk_"+int2string(i);
    int id =0;
    if(i == -3 ) id = 11;
    if(i == -2 ) id = 12;
    if(i == -1 ) id = 13;
    if(i == 1 ) id = 31;
    if(i == 2 ) id = 32;
    if(i == 3 ) id = 33;

    int sid = 0;
    if(i == -3 ) sid = 111;
    if(i == -2 ) sid = 121;
    if(i == -1 ) sid = 131;
    if(i == 1 ) sid = 341;
    if(i == 2 ) sid = 351;
    if(i == 3 ) sid = 361;

    this->fillKeyString(name,id);
    this->fillKeyRawId(id,name);
    this->fillKeyString(name+"near",sid);
    this->fillKeyRawId(sid,name+"near");
    this->fillKeyString(name+"far",sid+1);
    this->fillKeyRawId(sid+1,name+"far");
  }

}

std::string RPCDetIdStringAssociation::getKeyRawIdValue(int id){
  std::map<int,std::string>::iterator iter = _keyRawId.find(id);
  if( iter != _keyRawId.end() ) {
    return _keyRawId[id];
  }
  else{
    std::cout<< "Not value found for the selected key!"<< std::endl;
    return NULL;
  }
}

int RPCDetIdStringAssociation::getKeyStringValue(std::string chname){

  std::cout<<"inside getKeyString"<<std::endl;

  std::map<std::string,int>::const_iterator iter = _keyString.find(chname);
  if( iter != _keyString.end() ) {
    std::cout<<"GET DET ID: "<< iter->first<< "  "<< iter->second<<std::endl;
    return iter->second;
  }
  else{
    std::cout<< "Not value found for the selected key!"<< std::endl;
    return -999;
  }
}

void RPCDetIdStringAssociation::fillKeyString(std::string chname ,int id){
   //std::cout << chname << " " << id << std::endl;
  _keyString.insert( make_pair( chname, id) );
}

void RPCDetIdStringAssociation::fillKeyRawId(int id,std::string chname){
  _keyRawId.insert( make_pair( id,chname) );
}

std::string RPCDetIdStringAssociation::int2string(int i){
  std::stringstream ss;
  ss << i;
  std::string s= ss.str();
  return s;
}
