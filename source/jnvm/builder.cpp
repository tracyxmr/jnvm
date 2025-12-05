#include <jnvm/builder.hpp>
#include <jnvm/opcode.hpp>

void jnvm::Builder::bipush( const std::int32_t value )
{
    emit_bytes< std::int32_t >( Opcode::BIPUSH, value );
}

void jnvm::Builder::istore( const std::int8_t idx )
{
    emit_bytes< std::int32_t >( Opcode::ISTORE, idx );
}

void jnvm::Builder::iload( const std::int8_t idx )
{
    emit_bytes< std::int32_t >( Opcode::ILOAD, idx );
}

void jnvm::Builder::iadd( )
{
    emit( Opcode::IADD );
}
