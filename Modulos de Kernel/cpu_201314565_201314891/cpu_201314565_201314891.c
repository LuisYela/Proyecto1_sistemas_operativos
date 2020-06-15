#include <linux/proc_fs.h>
#include <linux/seq_file.h> 
#include <asm/uaccess.h> 
#include <linux/hugetlb.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/fs.h>
#include <linux/sched/signal.h>

#define BUFSIZE  	300

char * obtener_estado(long state)
{ 
	if(state==-1){
		return "No ejecutable";	
	}else if(state==1){
		return "En ejecucion";
	}else if(state==0){
		return "Ejecutable";
	}else if(state>0){
		return "Detenido";
	}else{
		return "Desconocido";
	}
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modulo que muestra el estado del CPU");
MODULE_AUTHOR("Danilo Urias Coc 201314565 | Luis Javier Yela 201314891");

static int crear_archivo(struct seq_file * archivo, void *v) {	
   	
	seq_printf(archivo, "  Carne: 201314565  | 201314891         \n");
    	seq_printf(archivo, "  Danilo Urias Coc  | Luis Javier Yela  \n");
 	struct task_struct *task;		//Cada Struct_task representa un un proceso del sistema
	struct task_struct *task_child;		
	struct list_head *list;
	for_each_process(task){
		seq_printf(archivo,"\nPID: %d | PROCESO:%s	| ESTADO: %s",task->pid, task->comm, obtener_estado(task->state));
		list_for_each(list, &task->children){
			task_child = list_entry( list, struct task_struct, sibling );
			seq_printf(archivo,"\n		PID PADRE:%s[%d] | PID: %d | PROCESO:%s		| ESTADO: %s",task->comm, task->pid,task_child->pid, task_child->comm, obtener_estado(task_child->state));
		}
	}
       
	return 0;
}

static int al_abrir(struct inode *inode, struct  file *file) {
  return single_open(file, crear_archivo, NULL);
}

static struct file_operations operaciones_archivo =
{    
    .open = al_abrir,
    .read = seq_read
};

static int al_cargar(void)
{
    proc_create("cpu_201314565_201314891", 0, NULL, &operaciones_archivo);
    printk(KERN_INFO "Carnet: 201314565 | 201314891\n");
    return 0;
}
 
static void al_descargar(void)
{
    remove_proc_entry("cpu_201314565_201314891", NULL);
    printk(KERN_INFO "Curso: Sistemas Operativos 1 Seccion:N\n");
    
}
 
module_init(al_cargar);
module_exit(al_descargar);

