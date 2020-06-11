#include <linux/proc_fs.h>
#include <linux/seq_file.h> 
#include <asm/uaccess.h> 
#include <linux/hugetlb.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/fs.h>

#define BUFSIZE  	150

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Muestra el estado actual de la memoria");
MODULE_AUTHOR("Danilo Urias Coc 201314565 | Luis Javier Yela 201314891");

struct sysinfo inf;

static int crear_archivo(struct seq_file * archivo, void *v) {	
    si_meminfo(&inf);
    long total_memo = (inf.totalram * 4);
    long free_memo = (inf.freeram * 4 );   
    seq_printf(archivo, "  Carne: 201314565  | 201314891         \n");
    seq_printf(archivo, "  Danilo Urias Coc  | Luis Javier Yela  \n");
    seq_printf(archivo, "  Memoria Total: \t %8lu KB - %8lu MB\n",total_memo, total_memo / 1024);
    seq_printf(archivo, "  Memoria Libre: \t %8lu KB - %8lu MB \n", free_memo, free_memo / 1024);
    seq_printf(archivo, "  Porcentaje de memoria en uso: \t %8lu %%\n", (free_memo * 100)/ total_memo) ;
    return 0;
}

static int al_abrir(struct inode *inode, struct  file *file) {
  return single_open(file, crear_archivo, NULL);
}

static struct file_operations operaciones_archivos =
{    
    .open = al_abrir,
    .read = seq_read
};

static int al_cargar(void)
{
    proc_create("memory_201314565_201314891", 0, NULL, &operaciones_archivos);
    printk(KERN_INFO "Carnet: 201314565 | 201314891\n");
    return 0;
}
 
static void al_descargar(void)
{
    remove_proc_entry("memory_201314565_201314891", NULL);
    printk(KERN_INFO "Curso: Sistemas Operativos 1 Seccion:N\n");
}
 
module_init(al_cargar);
module_exit(al_descargar); 
