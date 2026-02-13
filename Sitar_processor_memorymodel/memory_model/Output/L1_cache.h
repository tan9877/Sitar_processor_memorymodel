	
	#ifndef L1_CACHE_H
	#define L1_CACHE_H
	//======================================
	//file L1_cache.h                                                  
	//Describes module L1_cache                                      
	//Auto-generated from input file "memory_model.sitar" on 2026-2-9 at time 6:44:0   
	 //(This design unit is parameterized. Generating code into a .h file only) 
	
	//======================================
	#include<iostream>
	#include<iomanip>

	//sitar core classes
	#include"sitar_module.h"
	#include"sitar_time.h"
	//user included files
	 
//----code block from file memory_model.sitar, line:169 ----

#include<cstring>
#include<cstdlib>
#include<iostream>
#include<mem_def.h>

//----end code block-------


	namespace sitar{

	template<int SIZE=512,int MEMORY_DELAY=1>
	class L1_cache:public module
	{

		public:
			//constructor
			L1_cache();
	 
			void runBehavior(const time& current_time);
			inline void _incrementPointer(unsigned int ptr_number){_pointer[ptr_number]++; _reexecute=true;}
			void _resetBehavior();

			
			//Auto-generated variables for recording state in behavior block
			private:
			static const unsigned int _num_pointers=2; //total pointers used by this module
			static const unsigned int _num_timers=1;  	//total timers used by this module
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
//----code block from file memory_model.sitar, line:158 ----

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
	L1_cache<SIZE,MEMORY_DELAY>::L1_cache()
	{
		using std::cout;
		_type="L1_cache";
	
		
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

//----code block from file memory_model.sitar, line:177 ----

	for (uint16_t i=0; i < SIZE; i++)
		{
			mem[i] = (uint8_t)i;
		}

//----end code block-------

_pointer_last_value[1]=7;
_pointer_last_value[0]=1;
	}





	

	//runBehavior 
	template<int SIZE,int MEMORY_DELAY>
	void  L1_cache<SIZE,MEMORY_DELAY>::runBehavior(const time& current_time)
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
//do-while statement , line:185
 int _dowhile_iteration;
for(_dowhile_iteration=1; _dowhile_iteration<=SITAR_ITERATION_LIMIT; _dowhile_iteration++)
{
//execute the sequence  
switch(_pointer[1])
{

case 0:
{

//wait-until statement , line:186
if(((((((current_time.phase()))==(0))))))
 _incrementPointer(1);
else
 break;
 }
case 1:
{ 
 
//code_block_statement 
//----code block from file memory_model.sitar, line:187 ----

		while(n_request.pull(req_t))
		{
		memcpy(&addr, req_t.data(), 1);
		addr = addr & 0x000000FF;
	        //log << endl<< "addr=0x"<< std::hex << addr<< std::dec;	
	        type =req_t.data()[4];
		specifier = req_t.data()[5];
		status = 0;
		if(specifier != WORD && specifier != DOUBLEWORD && specifier != QUADWORD)
			status = 1;
		if ( (addr + specifier) > SIZE)
			status = 2;
		if (addr % specifier != 0)
        		status = 3;
		
		}
		log<<endl<<"req_t="<<req_t.info();
		
//----end code block-------

 _incrementPointer(1);
}

case 2:
{ 
 
//code_block_statement 
//----code block from file memory_model.sitar, line:207 ----

    		resp_t.data()[0] = status;
		log << endl<<"status="<<(int)status;
    		if (status == 0 && (type == LOAD || type == IFETCH))
		{
        		memcpy(resp_t.data(), &mem[addr],specifier );
    		}
		else if(status == 0 && (type == STORE))
		{
			mem[addr] = addr & 0xFF;
			log<<endl<<"mem[addr]"<< (int)mem[addr];
		}
		
//----end code block-------

 _incrementPointer(1);
}

case 3:
{

//wait-for -time statement , line:221
_timer[0] = sitar::time(current_time)+sitar::time(((MEMORY_DELAY)),((0)));
 _incrementPointer(1);
}

case 4:
{
if(current_time>=_timer[0])
 _incrementPointer(1);
else
 break; 
}
case 5:
{

//wait-until statement , line:222
if(((((((current_time.phase()))==(1))))))
 _incrementPointer(1);
else
 break;
 }
case 6:
{ 
 
//code_block_statement 
//----code block from file memory_model.sitar, line:223 ----

    		while(n_response.push(resp_t));	
		log<<endl<<"resp_t="<<resp_t.info();
    		
//----end code block-------

 _incrementPointer(1);
}

case 7: break;
}

if(_pointer[1]< _pointer_last_value[1])  
break; //sequence has converged  
 else 
 if(_pointer[1]==_pointer_last_value[1] && (((((((current_time.cycle()))<(20)))))==true))
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
 		std::cerr<<"\nERROR:Iteration limit exceeded for do-while loop on line:185 in file memory_model.sitar";
		_pointer[1]=0;                                                               
		_incrementPointer(0);                                                                    
	}                                                                                              
	else if(_pointer[1]<_pointer_last_value[1])                                    
	{                                                                                               
		//sequence just converged;                                                              
		break;                                                                                  
	}                                                                                               
	else if (_pointer[1]==_pointer_last_value[1] && (((((((current_time.cycle()))<(20)))))==false))  
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
			std::cerr<<"\nERROR:Iteration limit exceeded in behavior block of module L1_cache.";
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
	void  L1_cache<SIZE,MEMORY_DELAY>::_resetBehavior()
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
