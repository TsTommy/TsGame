#ifndef ENABLE_PM_H_INCLUDED
#define ENABLE_PM_H_INCLUDED

struct enable_pm
{
	template<
		typename msg
		, typename Ret
		>
	Ret pm();

	template<
		typename msg
		, typename Ret
		, typename Arg1
		>
	Ret pm(Arg1);

	template<
		typename msg
		, typename Ret
		, typename Arg1
		, typename Arg2
		>
	Ret pm(Arg1);

	template<
		typename msg
		, typename Ret
		, typename Arg1
		, typename Arg2
		, typename Arg3
		>
	Ret pm(Arg1);

	template<
		typename msg
		, typename Ret
		, typename Arg1
		, typename Arg2
		, typename Arg3
		, typename Arg4
		>
	Ret pm(Arg1);

	template<
		typename msg
		, typename Ret
		, typename Arg1
		, typename Arg2
		, typename Arg3
		, typename Arg4
		, typename Arg5
		>
	Ret pm(Arg1);

	template<
		typename msg
		, typename Ret
		, typename Arg1
		, typename Arg2
		, typename Arg3
		, typename Arg4
		, typename Arg5
		, typename Arg6
		>
	Ret pm(Arg1);

	template<
		typename msg
		, typename Ret
		, typename Arg1
		, typename Arg2
		, typename Arg3
		, typename Arg4
		, typename Arg5
		, typename Arg6
		, typename Arg7
		>
	Ret pm(Arg1);

	template<
		typename msg
		, typename Ret
		, typename Arg1
		, typename Arg2
		, typename Arg3
		, typename Arg4
		, typename Arg5
		, typename Arg6
		, typename Arg7
		, typename Arg8
		>
	Ret pm(Arg1);
};

#define PM(CLASS,MSG) struct MSG{}; template<> void CLASS::pm<MSG>();
#define PM0(CLASS,MSG,RET) struct MSG{}; template<> RET CLASS::pm<MSG,RET>();
#define PM1(CLASS,MSG,RET,ARG1) struct MSG{}; template<> RET CLASS::pm<MSG,RET,ARG1>(ARG1);
#define PM2(CLASS,MSG,RET,ARG1,ARG2) struct MSG{}; template<> RET CLASS::pm<MSG,RET,ARG1>(ARG1,ARG2);

#endif //ENABLE_PM_H_INCLUDED
