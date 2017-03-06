	
	</div> <!-- End content wrapper -->
	<footer>
		&copy; Eric Davis
	</footer>
	
	<!-- Javascript to toggle yes/no confirmation of delete -->
	<script type="text/javascript">
		function toggle(id) {
	    	var elmt = document.getElementById(id);
    
	    	if (elmt) {
    			// If hidden, show element
        		var display = elmt.style.display;
				if (display == "none") {
        	    	elmt.style.display = "inline-block";
    	    	}
	         else {
         		// If already dispayed, hide element
        	    elmt.style.display = "none";
    	    	}
	    	}
		}
	</script>
</body>
</html>