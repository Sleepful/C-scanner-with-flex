#Resumen de enunciado

C -> scanner -> beamer(latex doc)


generacion archivo temporal (preprocesador)
-------------------------------------------
	
	C -> preprocesador -> archivo temporal

	reglas del preprocesador de c
		#include
			incluir archivo dentro del directorio como parte del fuente
			el nuevo archivo puede tener nuevas directivas a procesar
		#define
			nombre que sigue mismas reglas que variables, nombres que aparecen en el fuente
			deben ser reemplazados por la hilera dentro del #define
			NO se manejan macros con parametros (seria extra)


analisis lexico
---------------
	
	C -> archivo temporal -> scanner -> beamer

	escribir un scanner para el lenguaje de C completo, segun la documentacion de c
	algo asi como hacer una funcion `Get_Token()`
		al ser invocada regresa el siguiente token del fuente, en alguna estructura de datos
		apropiada, con cosas como: codigo de token, puntero al lexema, valor numerico del
		lexema, etc

		**recomendable hacer el `Get_Token()` reusable para futuros proyectos**
	
