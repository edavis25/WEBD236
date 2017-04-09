<div class="answer-form">
    Add an answer
    <form method="POST" action="@@answers/add_answer@@">
        <textarea name="answer-content" class="answer-textarea" rows="3"></textarea>
        <br />
        <input type="hidden" name="question-id" value="{{ $question->getId() }}" />
        <input type="submit" class="answer-submit" value="Post Answer" name="answer-button" />
    </form>

</div>