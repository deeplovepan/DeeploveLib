// ex1: show 
$('#showButton').click( function() { 
	$(' #disclaimer').show( ) ; 
}) ; 

// ex2: hide
$('#hideButton').click( function() {
	$(this).hide(); 
}); 

// ex3: check if element visible:
// is function check if element selected by  $('#disclaimer' )
// equal element selected by ':visible'
if($('#disclaimer' ).is(':visible') ) { 
	$('#disclaimer').hide(); 
} 

// ex4: use toggle function to show/hide
$('#toggleButton').click(function() {
		$('#disclaimer').toggle( ) ; 
}) ; 


// ex5: modify the title of UI
$(' #toggleButton').click(function() {
	if($('#disclaimer').is(':visible') ) { 
		$(this).val('Hide'); 
	} 
});

// ex6: create and insert element
// note: insertAfter & insertBefore
$('<input type="button" value="toggle" id="toggleButton">').insertAfter('#disclaimer');

// ex7: add element as child of an existing element
// note: prependTo & appendTo
$('<strong>START! </strong>').prependTo('#disclaimer');


// ex8: remove element 
$('#no- script').remove( ); 

// ex9: remove element with filter
$('#celebs tr').remove(':contains("Singer")'); 

// ex10: modify content
// our paragraphs will contain bold-faced text, but our h2 tags will contain 
// the entire content string exactly as defined, including the <strong> tags
$('p').html(' <strong>Warning! </strong> Text has been replaced … '); 
$('h2').text('<strong>Warning! </strong> Title elements can be …' ) ; 

// ex11: get content
alert($('h2: first').text()); 

// ex12: fade out animation
$('#disclaimer').fadeOut(); 

// ex13: toggle animation
$('#disclaimer').toggle('slow'); 

// ex14: slide toggle animation
$('#disclaimer').slideToggle('slow'); 


// ex15: callback function
$('#disclaimer').slideToggle('slow' , function() {
	alert('The slide has finished sliding!' )
}) ;














