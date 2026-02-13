	
	#ifndef MEMORY_H
	#define MEMORY_H
	//======================================
	//file Memory.h                                                  
	//Describes module Memory                                      
	//Auto-generated from input file "memory_model_new.sitar" on 2026-2-9 at time 12:6:5   
	 //(This design unit is parameterized. Generating code into a .h file only) 
	
	//======================================
	#include<iostream>
	#include<iomanip>

	//sitar core classes
	#include"sitar_module.h"
	#include"sitar_time.h"
	//user included files
	 
//----code block from file memory_model_new.sitar, line:200 ----

#include<cstring>
#include<cstdlib>
#include<iostream>
#include<mem_def.h>

//----end code block-------


	namespace sitar{

	template<int SIZE=512,int MEMORY_DELAY=1>
	class Memory:public module
	{

		public:
			//constructor
			Memory();
	 
			void runBehavior(const time& current_time);
			inline void _incrementPointer(unsigned int ptr_number){_pointer[ptr_number]++; _reexecute=true;}
			void _resetBehavior();

			
			//Auto-generated variables for recording state in behavior block
			private:
			static const unsigned int _num_pointers=2; //total pointers used by this module
			static const unsigned int _num_timers=3;  	//total timers used by this module
			static const unsigned int _num_if_flags=0; //total if_flags used
			
			//State holders 
			//the +1 for array size is to avoid zero-sized arrays
			unsigned int 	_pointer[_num_pointers+1];		//pointers for sequences
			time 	_timer[_num_timers+1];			//timers for wait statements
			bool		_if_flag[_num_if_flags+1];		//if_flags
			unsigned int    _pointer_last_value[_num_pointers+1];	//last value taken by each sequence pointer

	
			//other declarations
			public:
			 
inport<6> n_request;
outport<5> n_response;
//----code block from file memory_model_new.sitar, line:189 ----

        token<6> req_t;
        token<5> resp_t;
        uint32_t addr;
        uint8_t type;
        uint8_t specifier;
	uint8_t status;
	uint8_t mem[SIZE];

//----end code block-------


	};
	}
	//==========================================


	
	namespace sitar{
	//Constructor
	template<int SIZE,int MEMORY_DELAY>
	Memory<SIZE,MEMORY_DELAY>::Memory()
	{
		using std::cout;
		_type="Memory";
	
		
		//Initialize variables used by behavior block
		for( int i=0;i<int(_num_pointers);i++) _pointer[i]=0;
		for( int i=0;i<int(_num_timers  );i++)   _timer[i]=0;
		for( int i=0;i<int(_num_if_flags);i++) _if_flag[i]=0;
		_terminated=0;
		_reexecute=0;
	
		 
//---Initializing inport n_request---
n_request.setInstanceId("n_request");
addInport(&n_request,"n_request");

//---Initializing outport n_response---
n_response.setInstanceId("n_response");
addOutport(&n_response,"n_response");

//----code block from file memory_model_new.sitar, line:208 ----

	for (uint16_t i=0; i < SIZE; i++)
		{
			mem[i] = rand() & 0xFF;		//Random initialization of Memory
		}

//----end code block-------

_pointer_last_value[1]=12;
_pointer_last_value[0]=1;
	}





	

	//runBehavior 
	template<int SIZE,int MEMORY_DELAY>
	void  Memory<SIZE,MEMORY_DELAY>::runBehavior(const time& current_time)
	{
		(void)current_time; //shut up compiler warning if variable is unused
		using std::cout;
		using std::endl;
		
		if(_terminated==1) return;

				
		
			_reexecute=1;
			//any statement that moves the pointers will set the _reexecute flag
			//execute module behavior till convergence:
			for(int _sitar_iteration=1; (_sitar_iteration<=SITAR_ITERATION_LIMIT and _reexecute==1);_sitar_iteration++)
		
		{
			//Execute behavior block till convergence
			_reexecute=0;
			
			//Execute behavior block. Any statement that updates 
			//pointers will set the _reexecute flag
			 
switch(_pointer[0])
{

case 0 :
{
//do-while statement , line:216
 int _dowhile_iteration;
for(_dowhile_iteration=1; _dowhile_iteration<=SITAR_ITERATION_LIMIT; _dowhile_iteration++)
{
//execute the sequence  
switch(_pointer[1])
{

case 0:
{

//wait-until statement , line:217
if(((((((current_time.phase()))==(0))))))
 _incrementPointer(1);
else
 break;
 }
case 1:
{

//wait-for -time statement , line:218
_timer[0] = sitar::time(current_time)+sitar::time(((MEMORY_DELAY)),((0)));
 _incrementPointer(1);
}

case 2:
{
if(current_time>=_timer[0])
 _incrementPointer(1);
else
 break; 
}
case 3:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:219 ----

			log<<endl<<"----------Memory Recieving Request--------- ";
                       // log << endl<<"Request Recieved (by Memory) "<<req_t.info();
			while(n_request.pull(req_t)){
				memcpy(&addr, req_t.data(), 1);
				log << endl<<"Request Recieved (by Memory) "<<req_t.info();
				addr = addr & 0x000000FF;				//256B memory
	       		        //log << endl<< "addr=0x"<< std::hex << addr<< std::dec;	
	       		        type =req_t.data()[4];
				specifier = req_t.data()[5];
					status = 0;								//No error	
				if(specifier != WORD && specifier != DOUBLEWORD && specifier != QUADWORD)	//illegal specifiar
					status = 1;
				if ( (addr + specifier) > SIZE)		//larger than the cache size	
					status = 2;
				if (addr % specifier != 0) 		//Unaligned address
        				status = 3;
		
		}
		log<<endl;
		
//----end code block-------

 _incrementPointer(1);
}

case 4:
{

//wait-until statement , line:240
if(((((((current_time.phase()))==(0))))))
 _incrementPointer(1);
else
 break;
 }
case 5:
{

//wait-for -time statement , line:241
_timer[1] = sitar::time(current_time)+sitar::time(((MEMORY_DELAY)),((0)));
 _incrementPointer(1);
}

case 6:
{
if(current_time>=_timer[1])
 _incrementPointer(1);
else
 break; 
}
case 7:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:242 ----

    		resp_t.data()[0] = status;
		log << endl<<"status= "<<(int)status;
    		if (status == 0 && (type == LOAD || type == IFETCH))
		{
			log<<endl<<"---------LOADING FROM MEMORY---------";
        		memcpy(resp_t.data(), &mem[addr],specifier);		//Word, Double,Quad Word Addressed
			log<<endl<<"Loading " <<(int) specifier<<" Bytes from memory location " << addr;
    		}
		log << endl;
		
//----end code block-------

 _incrementPointer(1);
}

case 8:
{

//wait-until statement , line:258
if(((((((current_time.phase()))==(1))))))
 _incrementPointer(1);
else
 break;
 }
case 9:
{

//wait-for -time statement , line:259
_timer[2] = sitar::time(current_time)+sitar::time(((MEMORY_DELAY)),((0)));
 _incrementPointer(1);
}

case 10:
{
if(current_time>=_timer[2])
 _incrementPointer(1);
else
 break; 
}
case 11:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:260 ----

               
		if(status == 0 && (type == STORE))
		{
			log<<endl<<"---------STORING IN MEMORY---------";
			mem[addr] = addr & 0xFF;
		 	log<<endl<<"Storing " <<(int)mem[addr]<<" at memory location " << addr;
		}

		log<<endl<<"---------MEMORY RESPONDING---------";
    		while(n_response.push(resp_t));	
		log<<endl<<"MEMORY RESPONSE= "<<resp_t.info();
		log<<endl;
    		
//----end code block-------

 _incrementPointer(1);
}

case 12: break;
}

if(_pointer[1]< _pointer_last_value[1])  
break; //sequence has converged  
 else 
 if(_pointer[1]==_pointer_last_value[1] && (((((((current_time.cycle()))<(25)))))==true))
 {
//re-activate the sequence	
_pointer[1]=0;	
_reexecute=1;       	
}				
else break; //sequence has terminated			
 };
	//For loop will finish if									
	//the sequence inside do-while loop converges                                                   
	//OR the expression becomes false at the end of some execution of while loop                    
	//OR  if the iteration limit is exceeded.                                                       
	if (_dowhile_iteration>SITAR_ITERATION_LIMIT)   
	{                                                                                               
		//iteration limit exceeded. Throw error and                                             
		//terminate the do-while statement                                                      
 		std::cerr<<"\nERROR:Iteration limit exceeded for do-while loop on line:216 in file memory_model_new.sitar";
		_pointer[1]=0;                                                               
		_incrementPointer(0);                                                                    
	}                                                                                              
	else if(_pointer[1]<_pointer_last_value[1])                                    
	{                                                                                               
		//sequence just converged;                                                              
		break;                                                                                  
	}                                                                                               
	else if (_pointer[1]==_pointer_last_value[1] && (((((((current_time.cycle()))<(25)))))==false))  
	{                                                                                               
		//terminate the do-while statement                                                      
		_pointer[1]=0;                                                               
		_incrementPointer(0);                                                                    
	} ;                                                                                              
};                                                                                                   
case 1: break;
}

		
		}

		
			//if iteration limit has exceeded, throw error and stop simulation 
			if(_reexecute==1)
			{
			std::cerr<<"\nERROR:Iteration limit exceeded in behavior block of module Memory.";
			std::cerr<<"\nModule behavior did not converge within a phase .... stopping simulation";
			stop_simulation();
			}

		

		//check if behavior has terminated. 
		if(_pointer[0]==_pointer_last_value[0])
		{
			_terminated=true;
		}
		return;
	}
	
	//resetBehavior 
	template<int SIZE,int MEMORY_DELAY>
	void  Memory<SIZE,MEMORY_DELAY>::_resetBehavior()
	{
		//reset variables used by behavior block
		for( int i=0;i<int(_num_pointers);i++) _pointer[i]=0;
		for( int i=0;i<int(_num_timers  );i++)   _timer[i]=0;
		for( int i=0;i<int(_num_if_flags);i++) _if_flag[i]=0;
		_terminated=0;
		_reexecute=0;
	}


	
	}

			
	#endif
