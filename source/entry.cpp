#include "jnvm/machine.hpp"

#include <jnvm/builder.hpp>

///@brief The entry point of the application.
std::int32_t main( )
{
    jnvm::Builder b;

    std::println("[ Test the expression ]:");
    std::println("let a = 10;\n"
        "let b = 20;\n"
        "let result = a + b;\n");

    b.bipush( 10 );
    b.istore( 0 );
    b.bipush( 20 );
    b.istore( 1 );
    b.iload( 0 );
    b.iload( 1 );
    b.iadd(  );
    b.istore( 2 );

    b.disassemble_bytecode(  );
    std::println("{}", b.get_bytecode(  ));

    jnvm::Machine machine { b.get_bytecode(  ) };

    machine.execute( );

    return EXIT_SUCCESS;
}