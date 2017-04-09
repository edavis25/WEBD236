[[ if ($files && count($files) > 0) : ]]
<div id="attachments">
    <label><b>Attachments:</b></label>
    <ul>
    [[ foreach ($files as $file) : ]]
        <li>
            <a href="@@file/view/{{$file->getId()}}@@">[ View ]</a>
            <a href="@@file/download/{{$file->getId()}}@@">[ Download ]</a>
            [[ if ( $isAuthor || Authenticator::instance() -> can('question_edit')) : ]]
                <div class="delete-wrapper">
                    <a href="##" class="delete-button">[ Delete ]</a>&nbsp;
                    <div class="confirm-delete" style="display: none;">
                        <a href="@@file/delete/{{$file->getId()}}/{{$question->getId()}}@@"> yes</a> / <a href="##" class="delete-button">no</a>
                    </div>
                </div>
            [[ endif; ]]
            &nbsp;{{$file->getOrigName()}}
        </li>
    [[ endforeach; ]]
    </ul>
</div>
[[ endif; ]]