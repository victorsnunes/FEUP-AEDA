#include "date.h"
#include "AuxFunctions.h"
#include "product.h"
#include "order.h"
#include "client.h"
#include "employee.h"
#include "bakery.h"
#include "menu.h"
#include <iostream>

int main()
{
    Company* AnthonyCenter = new Company();

    fileManager(AnthonyCenter);

    menu(AnthonyCenter);


    return 0;
}
