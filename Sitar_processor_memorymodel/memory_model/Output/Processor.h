	
	#ifndef PROCESSOR_H
	#define PROCESSOR_H
	//======================================
	//file Processor.h                                                  
	//Describes module Processor                                      
	//Auto-generated from input file "memory_model_new.sitar" on 2026-2-9 at time 12:6:5   
	 //(This design unit is parameterized. Generating code into a .h file only) 
	
	//======================================
	#include<iostream>
	#include<iomanip>

	//sitar core classes
	#include"sitar_module.h"
	#include"sitar_time.h"
	//user included files
	 
//----code block from file memory_model_new.sitar, line:41 ----

#include<cstring>
#include<cstdlib>
#include<iostream>
#include<mem_def.h>

//----end code block-------


	namespace sitar{

	template<int EXECUTION_DELAY=2,int P_LOAD=50,int P_STORE=40>
	class Processor:public module
	{

		public:
			//constructor
			Processor();
	 
			void runBehavior(const time& current_time);
			inline void _incrementPointer(unsigned int ptr_number){_pointer[ptr_number]++; _reexecute=true;}
			void _resetBehavior();

			
			//Auto-generated variables for recording state in behavior block
			private:
			static const unsigned int _num_pointers=4; //total pointers used by this module
			static const unsigned int _num_timers=1;  	//total timers used by this module
			static const unsigned int _num_if_flags=2; //total if_flags used
			
			//State holders 
			//the +1 for array size is to avoid zero-sized arrays
			unsigned int 	_pointer[_num_pointers+1];		//pointers for sequences
			time 	_timer[_num_timers+1];			//timers for wait statements
			bool		_if_flag[_num_if_flags+1];		//if_flags
			unsigned int    _pointer_last_value[_num_pointers+1];	//last value taken by each sequence pointer

	
			//other declarations
			public:
			 
inport<5> n_response;
outport<6> n_request;
//----code block from file memory_model_new.sitar, line:28 ----

	token<6> req_t;
	token<5> resp_t;
	uint32_t addr;
	uint8_t type;
	uint8_t specifier;
	bool load_inst;
	bool store_inst;
	bool execution_complete=1;

//----end code block-------


	};
	}
	//==========================================


	
	namespace sitar{
	//Constructor
	template<int EXECUTION_DELAY,int P_LOAD,int P_STORE>
	Processor<EXECUTION_DELAY,P_LOAD,P_STORE>::Processor()
	{
		using std::cout;
		_type="Processor";
	
		
		//Initialize variables used by behavior block
		for( int i=0;i<int(_num_pointers);i++) _pointer[i]=0;
		for( int i=0;i<int(_num_timers  );i++)   _timer[i]=0;
		for( int i=0;i<int(_num_if_flags);i++) _if_flag[i]=0;
		_terminated=0;
		_reexecute=0;
	
		 
//---Initializing inport n_response---
n_response.setInstanceId("n_response");
addInport(&n_response,"n_response");

//---Initializing outport n_request---
n_request.setInstanceId("n_request");
addOutport(&n_request,"n_request");

_pointer_last_value[2]=2;
_pointer_last_value[3]=2;
_pointer_last_value[1]=20;
_pointer_last_value[0]=1;
	}





	

	//runBehavior 
	template<int EXECUTION_DELAY,int P_LOAD,int P_STORE>
	void  Processor<EXECUTION_DELAY,P_LOAD,P_STORE>::runBehavior(const time& current_time)
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
//do-while statement , line:59
 int _dowhile_iteration;
for(_dowhile_iteration=1; _dowhile_iteration<=SITAR_ITERATION_LIMIT; _dowhile_iteration++)
{
//execute the sequence  
switch(_pointer[1])
{

case 0:
{

//wait-until statement , line:60
if((((((((((current_time.phase()))==(1)))))))))
 _incrementPointer(1);
else
 break;
 }
case 1:
{

//wait-until statement , line:61
if(((((((((execution_complete)==(1)))))))))
 _incrementPointer(1);
else
 break;
 }
case 2:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:62 ----
	
			log<<endl<<"----------Processor IFETCH Request--------- ";
			addr = rand() & 0xFFFFFFFF;		//Random 32 bit address
			log<<endl<<"IFETCH addr= "<<addr;
			type = IFETCH;
			int rand_specifier = rand() % 3;	//Randomizing specifier also
			if(rand_specifier == 0) {
				specifier = WORD;
				addr = (addr >> 2) * 4; 	//Address word aligned
			}
			else if(rand_specifier == 1) {
				specifier = DOUBLEWORD;
				addr = (addr >> 3) * 8;		//Address doubleword aligned
			}
			else if(rand_specifier == 2) {
				specifier = QUADWORD;
				addr = (addr >> 4) * 16;	//Address quadword aligned
			}	
			log<<endl<<"IFETCH specifier= "<<(int)specifier;		
			log<<endl<<"IFETCH aligned addr= "<<addr;	
			memcpy(req_t.data(), &addr, 4);
			req_t.data()[4] = type;
			req_t.data()[5] = specifier;
			while(n_request.push(req_t));		// 6 byte wide Request Token 
			log<<endl<<"IFETCH REQUEST (Processor Side)= "<<req_t.info()<<endl;
		
//----end code block-------

 _incrementPointer(1);
}

case 3:
{

//wait-until statement , line:90
if(((((((current_time.phase()))==(0))))))
 _incrementPointer(1);
else
 break;
 }
case 4:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:91 ----

			log<<endl<<"----------Processor Recieving Response--------- ";
			while(n_response.pull(resp_t));
			log<<endl<<"Response Recieved= "<<resp_t.info()<<endl;
			
		
//----end code block-------

 _incrementPointer(1);
}

case 5:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:99 ----

			execution_complete=0;
			log<<endl<<"----------Processor Executing----------"<<endl;
		
//----end code block-------

 _incrementPointer(1);
}

case 6:
{

//wait-until statement , line:104
if(((((((current_time.phase()))==(0))))))
 _incrementPointer(1);
else
 break;
 }
case 7:
{

//wait-for -time statement , line:105
_timer[0] = sitar::time(current_time)+sitar::time(((EXECUTION_DELAY)),((0)));
 _incrementPointer(1);
}

case 8:
{
if(current_time>=_timer[0])
 _incrementPointer(1);
else
 break; 
}
case 9:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:110 ----

			load_inst = (rand() % 100 < P_LOAD);
			if(load_inst){							
			        type = LOAD;
			        memcpy(req_t.data(), &addr, 4);
		      	 	req_t.data()[4] = type;
		      		req_t.data()[5] = specifier;
			}
		
//----end code block-------

 _incrementPointer(1);
}

case 10:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:120 ----
                                                                                                                                                                                   log<<endl<<"----------Execution Completed-----------"<<endl;
			execution_complete=1;
		
//----end code block-------

 _incrementPointer(1);
}

case 11:
{

//if statement , line:125
if((((((load_inst))))))
_if_flag[0]=true;
else
_if_flag[0]=false;
 _incrementPointer(1);
}

case 12:
{

if(_if_flag[0]==true)
{

switch(_pointer[2])
{

case 0:
{

//wait-until statement , line:126
if(((((((current_time.phase()))==(1))))))
 _incrementPointer(2);
else
 break;
 }
case 1:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:127 ----

				while(n_request.push(req_t));
				log<<endl<<"LOAD REQUEST SENT (by Processor)= "<<req_t.info()<<endl;
			
//----end code block-------

 _incrementPointer(2);
}

case 2: break;
}

}

else
{

}

if((_if_flag[0]==true && _pointer[2]>=_pointer_last_value[2]) || (_if_flag[0]==false))

{
 //if-statement has terminated
 _incrementPointer(1);
 _pointer[2]=0;

}

 else 
 //if-statement has converged
 break;
}

case 13:
{

//wait-until statement , line:135
if(((((((current_time.phase()))==(0))))))
 _incrementPointer(1);
else
 break;
 }
case 14:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:136 ----

			        while(n_response.pull(resp_t));
		       		log<<endl<<"LOAD RESPONSE RECIEVED (by Processor)= "<<resp_t.info();
                	
//----end code block-------

 _incrementPointer(1);
}

case 15:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:143 ----

			store_inst = (rand() % 100 < P_STORE);
			if(store_inst)
			{
		        	type = STORE;
		        	memcpy(req_t.data(), &addr, 4);
		        	req_t.data()[4] = type;
		        	req_t.data()[5] = specifier;
			}
		
//----end code block-------

 _incrementPointer(1);
}

case 16:
{

//if statement , line:156
if((((((store_inst))))))
_if_flag[1]=true;
else
_if_flag[1]=false;
 _incrementPointer(1);
}

case 17:
{

if(_if_flag[1]==true)
{

switch(_pointer[3])
{

case 0:
{

//wait-until statement , line:157
if(((((((current_time.phase()))==(1))))))
 _incrementPointer(3);
else
 break;
 }
case 1:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:158 ----

				while(n_request.push(req_t));
				log<<endl<<"STORE REQUEST SENT (by Processor= )"<<req_t.info();
			
//----end code block-------

 _incrementPointer(3);
}

case 2: break;
}

}

else
{

}

if((_if_flag[1]==true && _pointer[3]>=_pointer_last_value[3]) || (_if_flag[1]==false))

{
 //if-statement has terminated
 _incrementPointer(1);
 _pointer[3]=0;

}

 else 
 //if-statement has converged
 break;
}

case 18:
{

//wait-until statement , line:164
if(((((((current_time.phase()))==(0))))))
 _incrementPointer(1);
else
 break;
 }
case 19:
{ 
 
//code_block_statement 
//----code block from file memory_model_new.sitar, line:165 ----

		        while(n_response.pull(resp_t));
		        log<<endl<<"STORE RESPONSE RECIEVED (by Processor)= "<<resp_t.info()<<endl;
                
//----end code block-------

 _incrementPointer(1);
}

case 20: break;
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
 		std::cerr<<"\nERROR:Iteration limit exceeded for do-while loop on line:59 in file memory_model_new.sitar";
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
			std::cerr<<"\nERROR:Iteration limit exceeded in behavior block of module Processor.";
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
	template<int EXECUTION_DELAY,int P_LOAD,int P_STORE>
	void  Processor<EXECUTION_DELAY,P_LOAD,P_STORE>::_resetBehavior()
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
