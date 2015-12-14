using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;
using System.ComponentModel;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

namespace EngineCore
{
    [TypeDescriptionProvider(typeof(BaseObjectTypeDescriptionProvider))]
    [Serializable()] 
    public class BaseObject //: ISerializable
    {
        [NonSerialized] public ICore core = null;

        public virtual string ObjectName
        {
            get { return GetType().FullName; }
        }

        // FIXME
        public List<BaseComponent> objects = null;

        public BaseObject()
        {
            objects = new List<BaseComponent>();
        }

        public T GetComponent<T>() where T : BaseComponent      
        {
            try
            {
                Type cmp = typeof(T);

                foreach (T obj in objects)
                {
                    if (obj.GetType() == cmp)
                    {
                        return obj;
                    }
                }
            }
            catch 
            {
                // log - invalid cast
            }
            finally
            {

            }

            return null;
        }

        public void AddComponent(BaseComponent component)
        {
            objects.Add(component);
            component.parent = this;
        }

        public virtual void Update()
        {
            foreach(BaseComponent comp in objects)
            {
                comp.Update();
            }
        }

        public virtual void PostLoad()
        {
            foreach (BaseComponent comp in objects)
            {
                comp.PostLoad();
            }
        }

        public virtual void Render()
        {

        }

        //public  System.ComponentModel.PropertyDescriptorCollection GetProperties(object component, System.Attribute[] attributes)
        //{
        //    PropertyDescriptorCollection props;
        //    if (attributes == null)
        //        props = TypeDescriptor.GetProperties(component);
        //    else
        //        props = TypeDescriptor.GetProperties(component, attributes);

        //    PropertyDescriptor[] propArray = new PropertyDescriptor[props.Count];
        //    for (int i = 0; i < props.Count; i++)
        //    {
        //        // Create a new PropertyDescriptor from the old one, with 
        //        // a CategoryAttribute matching the name of the type.
        //        propArray[i] = TypeDescriptor.CreateProperty(props[i].ComponentType, props[i], new CategoryAttribute(props[i].PropertyType.Name));
        //    }
        //    return new PropertyDescriptorCollection(propArray);
        //}

        //public  System.ComponentModel.PropertyDescriptorCollection GetProperties(object component)
        //{
        //    return this.GetProperties(component, null);
        //}
    }


    class BaseObjectTypeDescriptionProvider : TypeDescriptionProvider
    {
        private static TypeDescriptionProvider defaultTypeProvider =
                       TypeDescriptor.GetProvider(typeof(BaseObject));

        public BaseObjectTypeDescriptionProvider()
            : base(defaultTypeProvider)
        {
        }

        public override ICustomTypeDescriptor GetTypeDescriptor(Type objectType,
                                                                object instance)
        {
            ICustomTypeDescriptor defaultDescriptor =
                                  base.GetTypeDescriptor(objectType, instance);

            //return instance == null ? defaultDescriptor :
            //    new TitleCustomTypeDescriptor(defaultDescriptor, instance);

            return defaultDescriptor;
        }
    }

//class BaseObjectCustomTypeDescriptor : CustomTypeDescriptor
//{
//    public BaseObjectCustomTypeDescriptor(ICustomTypeDescriptor parent, object instance)
//        : base(parent)
//    {
//        Title title = (Title)instance;

//        customFields.AddRange(CustomFieldsGenerator.GenerateCustomFields(title.Category)
//            .Select(f => new CustomFieldPropertyDescriptor(f)).Cast<PropertyDescriptor>());

//    }

//    private List<PropertyDescriptor> customFields = new List<PropertyDescriptor>();

//    public override PropertyDescriptorCollection GetProperties()
//    {
//        return new PropertyDescriptorCollection(base.GetProperties()
//            .Cast<PropertyDescriptor>().Union(customFields).ToArray());
//    }

//    public override PropertyDescriptorCollection GetProperties(Attribute[] attributes)
//    {
//        return new PropertyDescriptorCollection(base.GetProperties(attributes)
//            .Cast<PropertyDescriptor>().Union(customFields).ToArray());
//    }

//}
}
