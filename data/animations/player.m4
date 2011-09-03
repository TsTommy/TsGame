define(`frame',``
		frame {
			image = "player/'$1`'eval($2,`10',`4')`.png"
			duration = "$5"
			hotspot {
				x = "$3"
				y = "$4"
			}
		}
'')

define(`frames',``
		'ifelse($2,`1',`',`frames($1,decr($2),$3,$4,$5)')`
		'frame($1,$2,$3,$4,$5)`
'')

define(`weird_sequence',``
	'$1` {
		'frames($6,$2,$3,$4,$5)`
	}
'')

define(`sequence',``
	'$1` {
		'frames($1,$2,$3,$4,$5)`
	}
'')

animation
{
	sequence(`standing',`1',`179',`455',`1000')
	sequence(`jump',`1',`179',`455',`1000')
	sequence(`fall',`1',`179',`455',`1000')
	weird_sequence(`walking',`30',`179',`420',`40',`running')
	sequence(`running',`30',`179',`420',`10')
}
