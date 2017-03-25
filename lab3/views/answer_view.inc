<div class="answer">
    Posted {{ $answer->getDate() }} by 
    
    <a href="@@user/view_user/{{ $answer->getUserId() }}@@">{{ User::getFullName($answer->getUserId()) }}</a>
    
    <div class="answer-content">
        {{ nl2br($answer->getContent()) }}
    </div>
    
    [[ if (isLoggedIn() && $_SESSION['UserID'] == $answer->getUserId()) : ]]
        <div class="delete-wrapper">
            <a href="#" class="delete-button">[ Delete ]</a>&nbsp;
            <div class="confirm-delete" style="display: none;"> 
                <a href="@@answers/delete_answer/{{ $answer->getId() }}@@"> yes</a> / <a href="#" class="delete-button">no</a>
            </div>
        </div>
      
    [[ endif; ]]
</div>
