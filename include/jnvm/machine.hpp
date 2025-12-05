#pragma once

#include <memory>
#include <print>
#include <vector>
#include <jnvm/opcode.hpp>

namespace jnvm
{
    ///@brief A class to hold information about a function when it is invoked.
    class StackFrame
    {
    public:
        std::vector< std::uint32_t > locals { }; ///@brief Local variable array for the function.
        std::vector< std::uint32_t > operand_stack { }; ///@brief Operand stack for the function.
        std::uint32_t function_id;  ///@brief The current ID of the function being executed.
        std::uint32_t pc;           ///@brief Program counter offset.

        explicit StackFrame(
            const std::uint32_t function_id = 0,
            const std::uint32_t pc = 0
        ) :
            function_id { function_id },
            pc { pc }
        { }

        ///@brief Push a value onto the operand stack.
        void push( const std::uint32_t value )
        {
            operand_stack.push_back( value );
        }

        ///@brief Pop back value off the operand stack.
        std::uint32_t pop( )
        {
            const std::uint32_t value { operand_stack.back(  ) };
            operand_stack.pop_back(  );
            return value;
        }

        ///@brief Retrieve a local variable by index.
        [[nodiscard]]
        std::uint32_t get_local( const std::size_t idx ) const
        {
            return locals[ idx ];
        }

        ///@brief Set a local variable's value from its index with its new / first value
        void set_local( const std::size_t idx, const std::uint32_t value )
        {
            if ( idx >= locals.size(  ) ) locals.resize( idx + 1 );
            locals[ idx ] = value;
        }
    };

    class Machine
    {
    public:
        explicit Machine(
            std::vector< std::uint32_t > bytecode
        ) : m_bytecode { std::move( bytecode ) }
        {
            m_current_frame = std::make_unique< StackFrame >( 0, m_pc );
        }

        ///@brief Execute the program.
        void execute( );

    private:
        ///@brief The bytecode to be executed.
        std::vector< std::uint32_t > m_bytecode;

        ///@brief The current frame function which is being executed.
        std::unique_ptr< StackFrame > m_current_frame { nullptr };

        ///@brief Program counter.
        std::uint32_t m_pc { 0 };

        ///@brief Execute the bipush instruction.
        void execute_bipush( );
        ///@brief Execute the istore instruction.
        void execute_istore( );
        ///@brief Execute the iload instruction.
        void execute_iload( );
        ///@brief Execute the iadd instruction.
        void execute_iadd( );

        ///@brief Increment the program counter.
        void advance( ) { m_pc++; }
    };
}