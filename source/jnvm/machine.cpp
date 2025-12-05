#include <print>
#include <jnvm/machine.hpp>

void jnvm::Machine::execute( )
{
    while ( m_pc < m_bytecode.size(  ) )
    {
        switch ( auto opcode { m_bytecode[ m_pc ] } )
        {
            case Opcode::BIPUSH: execute_bipush(  );    break;
            case Opcode::ISTORE: execute_istore(  );    break;
            case Opcode::ILOAD:  execute_iload(  );     break;
            case Opcode::IADD:   execute_iadd(  );      break;
            default:             advance(  );           break;
        }
    }

    std::println("StackFrame@Locals = {}", m_current_frame->locals);
    std::println("StackFrame@OperandStack = {}", m_current_frame->operand_stack);
    std::println("StackFrame@PC = {}", m_current_frame->pc);
}

void jnvm::Machine::execute_bipush( )
{
    if ( m_current_frame != nullptr )
    {
        advance(  );
        const auto operand { m_bytecode[ m_pc++ ] };
        m_current_frame->push( operand );
    }
}

void jnvm::Machine::execute_istore( )
{
    if ( m_current_frame != nullptr )
    {
        advance(  );
        const auto idx { m_bytecode[ m_pc ] };
        advance(  );
        const auto value { m_current_frame->operand_stack.back(  ) };

        m_current_frame->operand_stack.pop_back(  );
        m_current_frame->set_local( idx, value );
    }
}

void jnvm::Machine::execute_iload( )
{
    if ( m_current_frame != nullptr )
    {
        advance(  );
        const auto idx { m_bytecode[ m_pc ] };
        advance(  );
        const auto value { m_current_frame->get_local( idx ) };

        m_current_frame->push( value );
    }
}

void jnvm::Machine::execute_iadd( )
{
    if ( m_current_frame != nullptr )
    {
        advance(  );
        const auto value1 { m_current_frame->pop(  ) };
        const auto value2 { m_current_frame->pop(  ) };
        const auto result { value1 + value2 };

        m_current_frame->push( result );
    }
}
