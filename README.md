h1. Задание

Пусть ваша поисковая система возвращает не любые документы, а документы с самой высокой релевантностью. Напишите функцию FindTopDocuments, которая должна находить только MAX_RESULT_DOCUMENT_COUNT = 5 результатов. Объявите эту глобальную константу вверху своего решения. Функцию FindTopDocuments поместите там же, где для вывода итогового результат мы вызывали FindDocuments. Саму FindDocuments замените на функцию FindAllDocuments, которая будет возвращать все результаты поиска в виде пар из идентификатора документа и релевантности {document_id, relevance}. Отсортируйте результат FindAllDocuments по убыванию, чтобы использовать его в FindTopDocuments.

h1. Примеры

h2. Ввод

<pre>
a the on cat
6
a fat cat sat on a mat and ate a fat rat
fat rat
a fat cat rat
a fat cat sat
a fat cat
a fat dog
funny fat cat on a mat with rat 
</pre>

h2. Вывод

<pre>
{ document_id = 0, relevance = 3 }
{ document_id = 2, relevance = 2 }
{ document_id = 1, relevance = 2 }
{ document_id = 5, relevance = 1 }
{ document_id = 4, relevance = 1 } 
</pre>
