%% views/header.inc %%

<h1>{{$question['Title']}}</h1>
<hr />
<p>Posted on: {{$question['Date']}} by <a href="@@user/view_user/{{ $question['UserID'] }}@@">{{ $question['Author'] }}</a></p>
<p>Tags: {{ ($question['Tags']) ? $question['Tags'] : "<i>none</i>" }}</p>
<p class="question-content">{{ nl2br($question['Content']) }}</p>

<a href="@@questions/edit_question/{{ $question['QuestionID'] }}@@">[Edit]</a>
<a href="#" onclick="toggle('confirm-delete')">[Delete]</a>
<div id="confirm-delete" style="display: none;">Are you sure? <a href="@@questions/delete_question/{{ $question['QuestionID'] }}@@">yes</a> / <a href="#" onclick="toggle('confirm-delete')">no</a></div>
<br /><br />
<a href="@@index@@">&lt;&lt; Back</a>

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

%% views/footer.inc %%
