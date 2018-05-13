#ifndef IDT_H
#define IDT_H

class IDT
{
    public:
        IDT();
        const static int SIZE = 256;
    private:
        void idt_set_gate(unsigned char num, unsigned long base, 
                unsigned short sel, unsigned char flags);
        void init();
};

#endif /* IDT_H */
