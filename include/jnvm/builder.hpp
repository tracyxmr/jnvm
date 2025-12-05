#pragma once

#include <jnvm/opcode.hpp>
#include <format>
#include <string>
#include <span>
#include <vector>
#include <print>

namespace jnvm
{
    class Builder
    {
    public:
        explicit Builder( ) = default;
        ~Builder( ) = default;

        ///@brief Push an immediate signed int value onto the operand stack.
        void bipush( std::int32_t value );

        ///@brief Store an integer into the current frame's local variable by index
        ///@param idx The index to which the integer should be stored in the local variable array of the current frame.
        ///@details The value on the top of the operand stack must be of type int, it is popped from the operand stack,
        ///and the value of the local variable at idx is set to that value popped.
        void istore( std::int8_t idx );

        ///@brief Load an integer from the current frame's local variable array.
        ///@param idx The index to which the integer should be loaded from in the local variable array of the current frame.
        ///@details The value of the local variable is pushed onto the operand stack.
        void iload( std::int8_t idx );

        ///@brief Top values of the operand stack are popped (must be int) and added, the result is stored on the operand stack.
        void iadd( );

        ///@brief Returns a reference to the bytecode of the builder.
        [[nodiscard]]
        const std::vector< std::uint32_t >& get_bytecode( ) const
        {
            return m_bytecode;
        }

        ///@brief Disassemble the bytecode into a readable format.
        void disassemble_bytecode( ) const
        {
            std::string output;
            std::size_t ptr { 0 };
            while ( ptr < m_bytecode.size(  ) )
            {
                switch ( auto byte { m_bytecode[ ptr ] } )
                {
                    case Opcode::BIPUSH:
                    {
                        ptr++;
                        const auto operand { m_bytecode[ ptr++ ] };
                        output += std::format("| {:0>4} | {:^15} | {:^15} |\n", ptr - 1, "bipush", std::format("immediate {}", operand));
                        break;
                    }
                    case Opcode::ISTORE:
                    {
                        ptr++;
                        const auto operand { m_bytecode[ ptr++ ] };
                        output += std::format("| {:0>4} | {:^15} | {:^15} |\n", ptr - 1, "istore", std::format("index {}", operand));
                        break;
                    }
                    case Opcode::ILOAD:
                    {
                        ptr++;
                        const auto operand { m_bytecode[ ptr++ ] };
                        output += std::format("| {:0>4} | {:^15} | {:^15} |\n", ptr - 1, "iload", std::format("index {}", operand));
                        break;
                    }
                    case Opcode::IADD:
                    {
                        output += std::format("| {:0>4} | {:^15} | {:^15} |\n", ptr, "iadd", "");
                        ptr++;
                        break;
                    }
                    default:
                    {
                        output += std::format("| {:0>4} | {:^15} | {:^15} |\n", ptr - 1, "unknown", std::format("{}", m_bytecode[ptr]));
                        ptr++;
                        break;
                    }
                }
            }

            std::println("| {:>4} | {:^15} | {:^15} |", "BCI", "INSTRUCTION", "OPERANDS");
            std::println("{}", output);
        }
    private:
        std::vector< std::uint32_t > m_bytecode;

        template< typename T >
        void emit( T byte )
        {
            m_bytecode.emplace_back( byte );
        }

        template< typename... Bytes >
        void emit_bytes( Bytes... bytes )
        {
            ( m_bytecode.push_back( std::forward< Bytes >( bytes ) ), ... );
        }
    };
}