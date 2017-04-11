<!DOCTYPE html>
<html>
    <head>
        <title>{{$title}}</title>
    </head>
    <body>
        <p>
            {{$name}}, <br />
            An account recovery email has been requested from IP address: <b>{{$ip}}</b><br />
            If you did not authorize this request, please contact the server administrator immediately.
        </p>
        <p>
            Your password: <b>{{$password}}</b>
        </p>
        <p>
            <i>Note:</i> It's probably a terrible idea to send you this email containing a plain-text password.
            Honestly, it's a terrible idea for us to even store passwords as plain-text in our database.<br />
            The good news is that you now know we have sub-standard security procedures!
        </p>
    </body>
</html>