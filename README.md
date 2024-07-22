## Lab 6 casita GLut  Rotar y zoom

![image](https://github.com/user-attachments/assets/b466ea15-9b38-4b91-a34d-af720be778e7)
## Lab 7.1 Sectores circulares, usando rojo, verde, azul y Glut 
![image](https://github.com/user-attachments/assets/924f0f73-3550-466f-9400-37a12d60e1ae)

## 7.2 Diferencias entre Marching Cubes y Delaunay

|Característica|Marching Cubes|Delaunay|
|--------------|--------------|--------|
|Dimensionalidad|3D|2D y 3D|
|Entrada|Campo escalar discreto 3D (vóxeles)|Conjunto de puntos en 2D o 3D|
|Salida|Malla poligonal de una isosuperficie|Triangulación que satisface el criterio de Delaunay|
|Algoritmo|Divide el espacio en cubos, determina los polígonos necesarios para representar la isosuperficie que pasa por cada cubo, y fusiona los polígonos individuales en la superficie deseada|Construye una triangulación que satisface el criterio de Delaunay, el cual especifica que el círculo circunscrito de cada triángulo no contiene ningún otro punto en su interior|
|Aplicaciones|Visualización médica (CT, MRI), efectos especiales, modelado 3D|Generación de mallas para simulaciones de elementos finitos, modelado de terreno, estimación de densidad de puntos|
|Propiedades|Genera una malla poligonal que aproxima la isosuperficie|Genera una triangulación óptima según ciertos criterios geométricos, como evitar triángulos alargados|

# Algoritmo de Marching Cubes

El algoritmo de Marching Cubes es un método utilizado en gráficos por computadora para extraer una malla poligonal de una superficie isosuperficial a partir de un campo escalar discreto tridimensional, comúnmente representado por voxels.

1. **División en Cubos**: El espacio se divide en una malla de cubos, donde cada cubo está formado por ocho vértices.
2. **Evaluación de Vértices**: Para cada cubo, se evalúan los valores escalares de sus ocho vértices. Dependiendo de si estos valores son mayores o menores que un valor umbral (iso-valor), se clasifica cada vértice como dentro o fuera de la superficie.
3. **Configuraciones de Triangulación**: Se generan índices para un arreglo precalculado que contiene 256 configuraciones posibles de triangulación para el cubo, basándose en la clasificación de los vértices. Sin embargo, en la práctica, solo hay 15 configuraciones únicas debido a simetrías.
4. **Interpolación de Vértices**: Los vértices de los triángulos generados se colocan interpolando linealmente entre los valores de los vértices del cubo que están adyacentes a la superficie isosuperficial.
5. **Fusión de Triángulos**: Finalmente, todos los triángulos generados se combinan para formar la superficie completa.

# Triangulación de Delaunay

1. **Inicialización Supertriángulo**: Comienza creando un triángulo grande (supertriángulo) que abarca todos los puntos que se van a triangulizar. Este triángulo es esencial para contener todos los puntos y facilitar la inserción inicial.
2. **Inserción de Puntos**: Para cada punto que se desea agregar, se realiza lo siguiente:
    - **Encontrar el triángulo que contiene el punto**: Se busca el triángulo existente que contiene el nuevo punto. Esto se puede hacer mediante un recorrido de búsqueda o utilizando estructuras de datos adecuadas.
3. **Formar Nuevos Triángulos**:
    - **Dividir el triángulo**: Una vez que se encuentra el triángulo que contiene al nuevo punto, se divide este triángulo en tres nuevos triángulos conectando el nuevo punto a cada uno de los vértices del triángulo encontrado.
4. **Actualización de la Triangulación**:
    - **Eliminar el triángulo original**: El triángulo que contenía el nuevo punto se elimina de la triangulación.
    - **Verificar la condición de Delaunay**: Para cada nuevo triángulo formado, se verifica si cumple con la condición de Delaunay, es decir, si el circuncírculo de cada triángulo está vacío de otros puntos. Si hay un punto dentro del circuncírculo, se realiza un intercambio de bordes (edge flip) para mantener la propiedad de Delaunay.
5. **Repetir**: Se repiten los pasos 2 a 4 para cada punto en el conjunto de datos hasta que todos los puntos hayan sido procesados.
6. **Finalización**:
    - **Eliminar el supertriángulo**: Finalmente, se eliminan los triángulos que comparten vértices con el supertriángulo, dejando solo la triangulación de Delaunay de los puntos originales.
