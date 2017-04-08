%% views/header.inc %%
<h1>{{ $title }}</h1>

<h2>Members</h2>
<table class="group-table">
[[ foreach ($members as $member) : ]]
    <tr>
        <td><a href="@@group/remove_member/{{$group->getId()}}/{{$member->getId()}}@@">Remove</a></td>
        <td>{{User::getFullName($member->getId())}}</td>
    </tr>
[[ endforeach; ]]
</table>

<h2>Non-members</h2>
<table class="group-table">
[[ foreach ($nonmembers as $nonmember) : ]]
    <tr>
        <td><a href="@@group/include_member/{{$group->getId()}}/{{$nonmember->getId()}}@@">Include</a></td>
        <td>{{User::getFullName($nonmember->getId())}}</td>
    </tr>
[[ endforeach; ]]
</table>

<br />
<a href="@@group/manage_groups@@">&lt;&lt; Back</a>
%% views/footer.inc %%