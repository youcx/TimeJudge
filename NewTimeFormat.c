#include <stdio.h>
#include <regex.h>
#include <string.h>
/**
 * @Desc:   将时间统一为YYYY-MM-DD HH:MM格式
 * @Date:   2019-09-03
 * @Author: youchuanxin
 * @Param:  srcTime 原时间串
 * 		    desTime 统一格式后的时间串
 * @Return: 1:success; 0:原时间格式错误; -1:传参错误
 *
 */
int transformTimeFormat(char *srcTime, char *desTime)
{
	if(NULL == srcTime || NULL == desTime)
		return -1;

	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int flag = 0;

	int status = -1;
	int pflag = REG_EXTENDED;
	regmatch_t pmatch[1];
	const size_t nmatch = 1;
	regex_t reg;
	const char *pattern = "^[0-9]{4}[/-][0-9]{1,2}[/-][0-9]{1,2} +[0-9]{1,2}:[0-9]{1,2}$";

	regcomp(&reg, pattern, pflag);
	status = regexec(&reg, srcTime, nmatch, pmatch, 0);
	regfree(&reg);
	if(status != 0){
		printf("no match\n");
		return 0;
	}else if(status == 0){
		printf("match success\n");
	}

	if(srcTime[4] == '/')
		flag = 1;
	else
		flag = 2;

	switch(flag)
	{
		case 1:
			sscanf(srcTime,"%d/%d/%d %d:%d",&year,&month,&day,&hour,&minute);
			break;
		case 2:
			sscanf(srcTime,"%d-%d-%d %d:%d",&year,&month,&day,&hour,&minute);
			break;
		default:
			return 0;
	}
	sprintf(desTime,"%d-%02d-%02d %02d:%02d",year,month,day,hour,minute);
	return 1;
}

int main()
{
	//test data
	char srcTime1[] = {"2019/5/15 14:02"};
	char srcTime2[] = {"2019-06-04 19:22"};
	char srcTime3[] = {"2019-06-03   03:52"};
	char srcTime4[] = {"2019/08/20 17:28"};
	char srcTime5[] = {"2019-7-7 0:25"};
	char srcTime6[] = {"2019-7-8 0:25:12"};
	char srcTime7[] = {"07/08/2018 0:25"};
	char srcTime8[] = {"07-08/2018 0:25"};
	char desTime[17];

	memset(desTime,0,sizeof(desTime));
	printf("%s\n",srcTime1);
	transformTimeFormat(srcTime1, desTime);
	printf("%s\n\n",desTime);

	printf("%s\n",srcTime2);
	transformTimeFormat(srcTime2, desTime);
	printf("%s\n\n",desTime);

	printf("%s\n",srcTime3);
	transformTimeFormat(srcTime3, desTime);
	printf("%s\n\n",desTime);

	printf("%s\n",srcTime4);
	transformTimeFormat(srcTime4, desTime);
	printf("%s\n\n",desTime);

	printf("%s\n",srcTime5);
	transformTimeFormat(srcTime5, desTime);
	printf("%s\n\n",desTime);

	printf("%s\n",srcTime6);
	transformTimeFormat(srcTime6, desTime);
	printf("%s\n\n",desTime);

	printf("%s\n",srcTime7);
	transformTimeFormat(srcTime7, desTime);
	printf("%s\n\n",desTime);

	printf("%s\n",srcTime8);
	transformTimeFormat(srcTime8, desTime);
	printf("%s\n\n",desTime);

	return 0;
}
