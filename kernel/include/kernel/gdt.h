#ifndef GDT_H
#define GDT_H

// based off of http://www.osdever.net/bkerndev/Docs/gdt.htm


class GDT
{
    public:
        GDT();

    private:
        /* Setup a descriptor in the Global Descriptor Table */
        void gdt_set_gate(int num, unsigned long base, unsigned long limit, 
                unsigned char access, unsigned char gran);
        void init();

        static const int SIZE = 3;
};

#endif /* GDT_H */

