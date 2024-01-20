#include "libft.h"

void	ft_stackadd_back(t_stack **stack, t_stack *new)
{
	if (!stack || !new)
		return ;
	if (!(*stack))
		*stack = new;
	else if (!(*stack)->next)
		(*stack)->next = new;
	else
		ft_stackadd_back(&(*stack)->next, new);
}

void	ft_stackadd_front(t_stack **stack, t_stack *new)
{
	if (!stack || !new)
		return ;
	if ((*stack))
		new->next = (*stack);
	*stack = new;
}

t_stack	*ft_stackbeforelast(t_stack *stack)
{
	if (!stack)
		return (NULL);
	if (!stack->next)
		return (stack);
	if (!stack->next->next)
		return (stack);
	return (ft_stackbeforelast(stack->next));
}

t_stack	*ft_stacklast(t_stack *stack)
{
	if (!stack)
		return (NULL);
	if (!stack->next)
		return (stack);
	return (ft_stacklast(stack->next));
}

t_stack	*ft_stacknew(int content)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->nb = -1;
	return (new);
}

int	ft_stacksize(t_stack *stack)
{
	if (!stack)
		return (0);
	return (1 + ft_stacksize(stack->next));
}
