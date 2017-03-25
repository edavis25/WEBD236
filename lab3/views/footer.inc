	
</div> <!-- End content wrapper -->
<footer>
    &copy; Eric Davis
</footer>

<!-- Javascript to toggle yes/no confirmation of delete -->
<script src="@@js/jquery-3.2.0.min.js@@"></script>



<script type="text/javascript">
    /*
    function toggle(id) {
        //var elmt = document.getElementById(id);
        var elmts = document.getElementsByClassName(id);
        if (elmt) {
            // If hidden, show element
            var display = elmt.style.display;
            if (display == "none") {
                elmt.style.display = "inline-block";
            } else {
                // If already dispayed, hide element
                elmt.style.display = "none";
            }
        }
    }
    */
      function toggle(element) {
        if (element) {
           var display = element.style.display;
           if (display == "none") {
               element.style.display = "inline-block";
           }
           else {
               element.style.display = "none";
           }
       }
    }
   
     $('.delete-button').on('click', function() {
        var parent = $(this).closest('div[class^="delete-wrapper"]');
        
        var div = parent.children();
        toggle(div[1]);
    });
    
 
    
  

</script>
</body>
</html>