#!/bin/perl

open(FILE, '<'.'./iec_std.csv');
my $type = '';
my $group = '';
my @vars = ();
my @funcs = ();
foreach(<FILE>)
{
    chomp $_;
    my @tmp = split(/;/, $_);

    if($_ =~ /_variables_types/)
    {
	$type = 'var';
	next;
    }

    if($_ =~ /_functions_type/)
    {
	$type = 'func';
	next;
    }

    if(length($tmp[0]) && $type eq 'func')
    {
	$group = $tmp[0]; $group =~ s/\_\(\"//; $group =~ s/\"\)//;
    }

    next if(!length($tmp[1]) || $tmp[1] =~ /\*/);

    if($type eq 'var')
    {
	my %var = (
	    'name' => $tmp[1],
	    'type' => $tmp[2],
	    'doc' => $tmp[3]
	);
	push(@vars, { %var });
    }

    if($type eq 'func')
    {
	my $i = $tmp[3]; $i =~ s/\(//; $i =~ s/\)//;
	my $doc = $tmp[5]; $doc =~ s/\_\(\"//; $doc =~ s/\"\)//;
	my %func = (
	    'name' => $tmp[1],
	    'group' => $group,
	    'i' => $i,
	    'o' => $tmp[4],
	    'doc' => $doc
	);
	push(@funcs, { %func });
    }
}
close(FILE);

foreach(@funcs)
{
    print '      <pou name="', $_->{'name'}, '" pouType="function">', "\n";

    print '        <interface>', "\n";
    print '          <returnType>', "\n";
    print '            <', $_->{'o'}, '/>', "\n";
    print '          </returnType>', "\n";
    print '          <inputVars>', "\n";
    my $counter = 0;
    foreach(split(/,/, $_->{'i'}))
    {
	print '            <variable name="var', $counter++, '">', "\n";
	print '              <type>', "\n";
	$_ =~ s/\s+//g;
	my $ref = 0;
	foreach my $v (@vars)
	{
	    if($v->{'name'} eq $_)
	    {
		$ref = 1;
		print '                 <', $v->{'type'}, '/>', "\n";
		print '              </type>', "\n";
	        print '              <documentation>', "\n";
		print '                <xhtpl:p><![CDATA[', $v->{'doc'}, ']]</xhtmp:p>', "\n";
		print '              </documentation>', "\n";
	    }
	}
	if($ref == 0)
	{
	    print '                 <', $_, '/>', "\n";
	    print '              </type>', "\n";
	}
	print '            </variable>', "\n";
    }
    print '          </inputVars>', "\n";
    print '        </interface>', "\n";

    print '        <body>', "\n";
    print '        </body>', "\n";

    print '        <addData>', "\n";
    print '          <data name="http://ambi.biz/plcopenxml/group" handleUnknown="discard">', "\n";
    print '            <group name="', $_->{'group'}, '"/>', "\n";
    print '          </data>', "\n";
    print '        </addData>', "\n";

    print '        <documentation>', "\n";
    print '          <xhtpl:p><![CDATA[', $_->{'doc'}, ']]</xhtmp:p>', "\n";
    print '        </documentation>', "\n";

    print '      </pou>', "\n";
}

