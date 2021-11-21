#define _3BC_DISABLE_INTERPRETER
#include <3bc.h>

/** TODO: auto detect **/
#define SERIAL_SPEED 9600

void setup()
{
    int count = 0;
    app_3bc_t app;
    app_3bc_t* apps;

    /** starts serial **/
    Serial.begin(SERIAL_SPEED);
    while(!Serial);

    /** count limit of virtual machines **/
    for(;lang_3bc_init() != NULL; count++);
    for(apps = ds_hypervisor_darray_get_all(); *apps != NULL; free(*apps++));

    /** depurate results **/
    Serial.write("\n3BC Machines limit: ");
    Serial.println(count);

    Serial.write("Machine size: ");
    Serial.print(sizeof(struct app_3bc_s));
    Serial.println(" bytes");

    Serial.write("Line size: ");
    Serial.print(sizeof(struct line_node_s));
    Serial.println(" bytes");

    Serial.write("Label size: ");
    Serial.print(sizeof(struct label_node_s));
    Serial.println(" bytes");
    
    Serial.write("Address size: ");
    Serial.print(sizeof(struct memory_node_s));
    Serial.println(" bytes");
    Serial.write("Address limit: ");
    Serial.println(sizeof(address_3bc_t) * 255);

    Serial.write("Value maximum: ");
    Serial.println((((sizeof(data_3bc_t)*255)/2)-1));
    Serial.write("Value minimum: -");
    Serial.println((((sizeof(data_3bc_t)*255)/2)));

    while(1);
}

void loop() {}
