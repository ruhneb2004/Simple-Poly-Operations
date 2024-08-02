#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// struct def

struct Term
{
    float coeff;
    int exp;
};

struct Poly
{
    int n;
    struct Term *t;
};

struct PolyDivRes
{
    struct Poly q;
    struct Poly r;
};

// function definition

int polyEval(int xValue, struct Poly p)
{
    int sum = 0;
    for (int i = 0; i < p.n; i++)
    {
        sum += p.t[i].coeff * pow(xValue, p.t[i].exp);
    }
    return sum;
}

// displaying the given polynomial!!!

void displayPoly(struct Poly p)
{
    for (int j = 0; j < p.n; j++)
    {
        printf("%.2fX%d ", p.t[j].coeff, p.t[j].exp);
        if (j != (p.n - 1) && p.t[j].coeff >= 0)
            printf("+ ");
        else if (p.t[j].coeff < 0)
        {
        }
        else
            printf("\n");
    }
}

// The p3 is the resultant poly made from the sum of the polys[0] and polys[1]

void polyAdd(struct Poly *polys, struct Poly *p3)
{

    int i = 0, j = 0, k = 0;
    p3->n = polys[0].n + polys[1].n;
    p3->t = (struct Term *)malloc(p3->n * sizeof(struct Term));

    while (i < polys[0].n && j < polys[1].n)
    {
        if (polys[0].t[i].exp == polys[1].t[j].exp)
        {
            p3->t[k].exp = polys[0].t[i].exp;
            p3->t[k].coeff = polys[0].t[i].coeff + polys[1].t[j].coeff;
            i++, j++, k++;
        }
        if (polys[0].t[i].exp > polys[1].t[j].exp)
        {
            p3->t[k].exp = polys[0].t[i].exp;
            p3->t[k].coeff = polys[0].t[i].coeff;
            k++, i++;
        }
        if (polys[0].t[i].exp < polys[1].t[j].exp)
        {
            p3->t[k].exp = polys[1].t[j].exp;
            p3->t[k].coeff = polys[1].t[j].coeff;
            k++, j++;
        }
    }

    for (; i < polys[0].n; i++)
    {
        p3->t[k++] = polys[0].t[i];
    }

    for (; j < polys[1].n; j++)
    {
        p3->t[k++] = polys[1].t[j];
    }

    p3->n = k;
}

void polySub(struct Poly *polys, struct Poly *p3)
{
    printf("I am here 5\n");
    int i = 0, j = 0, k = 0;
    p3->n = polys[0].n + polys[1].n;
    p3->t = (struct Term *)malloc(p3->n * sizeof(struct Term));

    while (i < polys[0].n && j < polys[1].n)
    {
        if (polys[0].t[i].exp == polys[1].t[j].exp)
        {
            int coeffDiff = polys[0].t[i].coeff - polys[1].t[j].coeff;
            if (coeffDiff != 0)
            {
                p3->t[k].exp = polys[0].t[i].exp;
                p3->t[k].coeff = polys[0].t[i].coeff - polys[1].t[j].coeff;
                k++;
            }
            i++, j++;
        }
        else if (polys[0].t[i].exp > polys[1].t[j].exp)
        {
            p3->t[k].exp = polys[0].t[i].exp;
            p3->t[k].coeff = polys[0].t[i].coeff;
            k++, i++;
        }
        else if (polys[0].t[i].exp < polys[1].t[j].exp)
        {
            p3->t[k].exp = polys[1].t[j].exp;
            p3->t[k].coeff = polys[1].t[j].coeff;
            k++, j++;
        }
    }

    for (; i < polys[0].n; i++)
    {
        p3->t[k++] = polys[0].t[i];
    }

    for (; j < polys[1].n; j++)
    {
        p3->t[k++] = polys[1].t[j];
    }

    p3->n = k;
}

void polyMul(struct Poly *polys, struct Poly *p3)
{
    p3->n = polys[0].n * polys[1].n;

    //! Why do we need the plus 2 here???

    int hashMapSize = polys[0].t[0].exp + polys[1].t[1].exp + 2;

    // This is taken as an assumption that the largest exponent is given first(You do have to do the input checking for ensuring that is the case but here it's fine though(I guess,and yes this is inside of inside of a bracket!))

    int hashMap[hashMapSize];
    for (int i = 0; i < hashMapSize; i++)
    {
        hashMap[i] = -1;
    }

    // In the hashmap we are giving the index as the exp and the occurence index in the p3 as input to the hashMap array!

    int k = 0;
    p3->t = (struct Term *)malloc(sizeof(struct Term) * p3->n);
    for (int i = 0; i < polys[0].n; i++)
    {
        for (int j = 0; j < polys[1].n; j++)
        {
            if (hashMap[polys[0].t[i].exp + polys[1].t[j].exp] == -1)
            {
                p3->t[k].coeff = polys[0].t[i].coeff * polys[1].t[j].coeff;
                p3->t[k].exp = polys[0].t[i].exp + polys[1].t[j].exp;
                hashMap[polys[0].t[i].exp + polys[1].t[j].exp] = k;
                k++;
            }
            else
            {
                p3->t[hashMap[polys[0].t[i].exp + polys[1].t[j].exp]].coeff += polys[0].t[i].coeff * polys[1].t[j].coeff;
            }
        }
    }

    p3->n = k;

    for (int j = 0; j < p3->n; j++)
    {
        printf("%fX%d ", p3->t[j].coeff, p3->t[j].exp);
        if (j != (p3->n - 1) && p3->t[j].coeff >= 0)
            printf("+ ");
        else if (p3->t[j].coeff < 0)
        {
        }
        else
            printf("\n");
    }
}

void polyDiv(struct Poly *polys, struct PolyDivRes *polyDivRes)
{
    if (polys[0].t[0].exp < polys[1].t[0].exp)
    {
        printf("Can't do division with p1 having lower power than p2!\n");
        return;
    }
    else if (polys[0].t == polys[1].t)
    {
        printf("The result is 1!\n");
        return;
    }

    //  I think the difference of the two poly's exp + 1  is the number of steps needed to be taken.

    int stepNumber = polys[0].t[0].exp - polys[1].t[0].exp + 1;
    polyDivRes->q.n = stepNumber;
    polyDivRes->r.n = polys[0].n;
    polyDivRes->q.t = (struct Term *)malloc(sizeof(struct Term) * polyDivRes->q.n);
    polyDivRes->r.t = (struct Term *)malloc(sizeof(struct Term) * polyDivRes->r.n);

    struct Poly dividentCopy = polys[0], substractor;
    substractor.t = (struct Term *)malloc(sizeof(struct Term) * polys[1].n);
    substractor.n = polys[1].n;
    int expDiff;
    float coeffDiff;
    int k = 0;

    printf("I am Here 1\n");

    for (int i = 0; i < stepNumber; i++)
    {
        expDiff = dividentCopy.t[0].exp - polys[1].t[0].exp;
        coeffDiff = dividentCopy.t[0].coeff / polys[1].t[0].coeff;

        // This coeff diff and the expDiff is a term in the quotient!

        polyDivRes->q.t[k].exp = expDiff;
        polyDivRes->q.t[k].coeff = coeffDiff;
        printf("I am here 2\n");

        // setting up the substractor. This is used for substracting the dividentCopy.

        for (int j = 0; j < polys[1].n; j++)
        {
            substractor.t[j].coeff = polys[1].t[j].coeff * polyDivRes->q.t[k].coeff;
            substractor.t[j].exp = polys[1].t[j].exp + polyDivRes->q.t[k].exp;
        }

        printf("I am here 3\n");
        // I had to do this, cause I provided the polynomials to be subbed as elements of the array earlier!
        struct Poly subPoly[2] = {dividentCopy, substractor};
        struct Poly tempRes;

        polySub(subPoly, &tempRes);

        printf("\nstart\n");
        displayPoly(tempRes);
        printf("end\n\n");

        dividentCopy = tempRes;

        printf("I am Here 4\n");

        k++;
    }
    free(substractor.t);
    polyDivRes->q.n = k;
    polyDivRes->r = dividentCopy;
}

int main()
{

    struct Poly polyAddRes, polyMulRes, polySubRes;
    struct PolyDivRes polyDivRes;
    int numberOfPoly;

    printf("If you want to do poly addition, substraction, multiplication and division, Enter 2 or for evaluating a poly enter 1\n");
    scanf("%d", &numberOfPoly);

    struct Poly *polys = (struct Poly *)malloc(sizeof(struct Poly) * numberOfPoly);

    for (int i = 0; i < numberOfPoly; i++)
    {

        printf("\nGive inputs for poly %d\n", i + 1);
        printf("Give me the number of non-zero terms\n");
        scanf("%d", &polys[i].n);

        // Poly array initialisation. The type casting is not required in C but it can help to improve the code readability and also can help to be more compatible with C++, as in C the malloc returns a void* so we have to type cast into the desired quantity.

        polys[i].t = (struct Term *)malloc(polys[i].n * sizeof(struct Term));

        printf("Enter the polynomial's terms\n");

        for (int j = 0; j < polys[i].n; j++)
        {
            printf("term %d\n", j + 1);
            scanf("%f %d", &polys[i].t[j].coeff, &polys[i].t[j].exp);
        }
        displayPoly(polys[i]);
    }

    if (numberOfPoly == 1)
    {
        int xValue;
        printf("\nGive the value for x\n");
        scanf("%d", &xValue);
        int polyEvalRes = polyEval(xValue, polys[0]);
        printf("With xValue = %d, the sum of the poly is %d\n", xValue, polyEvalRes);
    }
    else
    {
        polyAdd(polys, &polyAddRes);
        polySub(polys, &polySubRes);
        printf("The resultant poly after summing = ");
        displayPoly(polyAddRes);
        printf("The resultant poly after substraction = ");
        displayPoly(polySubRes);
        printf("The resultant poly after multiplication = ");
        polyMul(polys, &polyMulRes);
        displayPoly(polyMulRes);
        printf("The resultant poly after division = ");
        polyDiv(polys, &polyDivRes);
        printf("Quotient => \n");
        displayPoly(polyDivRes.q);
        printf("Remainder =>\n");
        displayPoly(polyDivRes.r);
    }

    free(polySubRes.t);
    free(polyAddRes.t);
    free(polyMulRes.t);
    free(polyDivRes.q.t);
    free(polyDivRes.r.t);
    free(polys);
}